KickPot - إصدار Windows مع ملف تثبيت

إنشاء ملف التثبيت KickPot-Setup.exe:
1) ارفع محتويات هذا المجلد إلى مستودع GitHub (بما فيها مجلد .github).
2) افتح تبويب Actions.
3) شغّل Build KickPot Windows Installer (أو انتظر التشغيل التلقائي بعد push).
4) بعد نجاح العملية، افتح التشغيل وانزل إلى Artifacts.
5) نزّل KickPot-Setup؛ ستجد داخله KickPot-Setup.exe.

يتطلب البناء Windows 2022 وQt 6 وVisual Studio Build Tools، ويتم تثبيت Inno Setup تلقائياً داخل GitHub Actions.
ملف التثبيت ينشئ اختصاراً في قائمة Start، ويمكن اختيار إنشاء اختصار على سطح المكتب.
