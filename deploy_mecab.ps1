Remove-Item -Recurse -Force "Textractor"
mkdir -Force -Verbose "Textractor";
foreach ($file in @(
  "Textractor.exe",
  "TextractorCLI.exe",
  "texthook.dll"
))
{
  copy -Force -Recurse -Verbose -Destination "Textractor" -Path "builds/_x86/$file";
}
foreach ($extension in @(
  "Bing Translate",
  "Copy to Clipboard",
  "DeepL Translate",
  "DevTools DeepL Translate",
  "DevTools Papago Translate",
  "DevTools Systran Translate",
  "Extra Newlines",
  "Extra Window",
  "Google Translate",
  "Lua",
  "Regex Filter",
  "Remove Repeated Characters",
  "Remove Repeated Phrases",
  "Remove Repeated Phrases 2",
  "Remove 30 Repeated Sentences",
  "Replacer",
  "Styler",
  "Thread Linker"
))
{
  copy -Force -Recurse -Verbose -Destination "Textractor/$extension.xdll" -Path "builds/_x86/$extension.dll";
}
foreach ($file in @(
  "LoaderDll.dll",
  "LocaleEmulator.dll",
  "Qt5Core.dll",
  "Qt5Gui.dll",
  "Qt5Network.dll",
  "Qt5WebSockets.dll",
  "Qt5WinExtras.dll"
  "Qt5Widgets.dll",
  "platforms",
  "styles",
  "Qt5TextToSpeech.dll",
  "libmecab.dll",
  "mecabrc",
  "dic",
  "texttospeech"
))
{
  copy -Force -Recurse -Verbose -Destination "Textractor/$file" -Path "builds/_x86/$file";
}