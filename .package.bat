@echo off

mkdir Twilight_Tempo
xcopy /Y fonts Twilight_Tempo\fonts\
xcopy /Y music Twilight_Tempo\music\
xcopy /Y sounds Twilight_Tempo\sounds\
xcopy /Y /E sprites Twilight_Tempo\sprites\
xcopy /Y SFML\bin\openal32.dll Twilight_Tempo
xcopy /Y SFML\bin\sfml-audio-2.dll Twilight_Tempo
xcopy /Y SFML\bin\sfml-graphics-2.dll Twilight_Tempo
xcopy /Y SFML\bin\sfml-system-2.dll Twilight_Tempo
xcopy /Y SFML\bin\sfml-window-2.dll Twilight_Tempo
echo F|xcopy /Y Release\Twilight_Tempo.exe "Twilight_Tempo\Twilight Tempo.exe"
pause