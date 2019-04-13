# TestTofuGui
Sample VS2017 project for testing if character glyphs can be rendered by a given window (font)


## Description

This is a sample project that followed from [this Stackover discussion](https://stackoverflow.com/questions/54050095/how-to-tell-if-a-surrogate-pair-unicode-character-is-supported-by-the-font) to demonstrate the concept.

For relevant code check `testGlyphs()` function in the [`TestTofuGuiDlg.cpp`](TestTofuGui/TestTofuGui/TestTofuGuiDlg.cpp) source file.

## Output

Here's the output on different OS's, some of which may not support all glyphs:

- Windows 10:

  ![alt text](images/Screenshot_Win10.PNG?raw=true "Windows 10")

- Windows 7:

  ![alt text](images/Screenshot_Win7.PNG?raw=true "Windows 7")
  
- Windows XP:

  ![alt text](images/Screenshot_WinXP.PNG?raw=true "Windows XP")
