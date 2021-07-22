#include "mecab/mecab.h"
#include <math.h>
#include "ui_extrawindow.h"
#include <QTextToSpeech>

#define CHECK(eval)                                               \
    if (!eval)                                                    \
    {                                                             \
        fprintf(stderr, "Exception:%s\n", mecab_strerror(mecab)); \
        mecab_destroy(mecab);                                     \
        return false;                                             \
    }
// common.h 有提供
class useMecab
{
public:
    useMecab(std::wstring &sentence, Ui::ExtraWindow &ui, int rowMax)
    {
        char *argv = "";
        int fontSize = ui.display->font().pointSize();
        int row_text_size = ceil(ui.display->width() / (fontSize * 2.2));
        if (rowMax)
        {
            row_text_size = rowMax;
        }

        mecab = mecab_new(0, &argv);
        convertStr(sentence);
        outputHtml(sentence, fontSize, row_text_size);
        sentence += translate_sentence;
    };
    ~useMecab()
    {
        mecab_destroy(mecab);
    };
    const char *char_sentence;
    std::wstring translate_sentence = L"\x200b \n";
    const mecab_node_t *node_sentence;

private:
    mecab_t *mecab;
    void convertStr(std::wstring &sentence)
    {
        QString input_qs(S(sentence));
        QStringList text_ary = input_qs.split(QString(S(L"\x200b \n")));
        QString origin_text = text_ary[0];
        if (text_ary.size() > 1)
            translate_sentence += text_ary[1].toStdWString();
        char *char_s = new char[origin_text.toStdString().length() + 1];
        strcpy(char_s, origin_text.toStdString().c_str());
        char_sentence = char_s;
        getMecabNode();
    };
    void getMecabNode()
    {
        node_sentence = mecab_sparse_tonode(mecab, char_sentence);
    };
    void outputHtml(std::wstring &sentence, int fontSize, int allowTextLen)
    {
        QString style = "<style>td{padding:0 1px;white-space:nowrap;}</style>";
        QString htmlText = "<tr>";

        int nowTableIndex = 0;
        int nowTextCount = 0;
        QStringList tdList;
        for (; node_sentence; node_sentence = node_sentence->next)
        {
            if (node_sentence->stat == MECAB_NOR_NODE || node_sentence->stat == MECAB_UNK_NODE)
            {
                // 當下解析字
                QString current_str(node_sentence->surface);
                current_str = current_str.trimmed();
                current_str.truncate(node_sentence->length / 3);
                QString pronounce(node_sentence->feature);
                QStringList pronounce_list = pronounce.split(QString(","));

                QString topText = "<td align=\"center\" style=\"font-size:" + QString::number(fontSize * 0.75) + "px;\">" + pronounce_list.takeLast() + "</td>";
                QString mainText = "<td align=\"center\">" + current_str + "</td>";

                nowTextCount += current_str.length();
                if (nowTextCount > allowTextLen)
                {
                    tdList[nowTableIndex * 2] += "</tr>";
                    tdList[nowTableIndex * 2 + 1] += "</tr></table>";
                    nowTableIndex++;
                    nowTextCount = current_str.length();
                }

                if (tdList.length() < (nowTableIndex + 1) * 2)
                {
                    tdList.push_back("<table><tr>" + topText);
                    tdList.push_back("<tr>" + mainText);
                }
                else
                {
                    tdList[nowTableIndex * 2] += topText;
                    tdList[nowTableIndex * 2 + 1] += mainText;
                }
                // tdList[nowRow] += topText;
                // tdList[nowRow] += mainText;
            }
        }
        sentence = (style + tdList.join("") + "</tr></table>").toStdWString();
    }
};
