@echo off
gcc src/main.c src/vehiculo.c src/calculos.c src/viaje.c src/archivo.c src/memoria.c src/mantenimiento.c src/utilidades.c -o vehiculos.exe -lm
if %errorlevel% neq 0 (
  echo Error al compilar.
  pause
  exit /b 1
)
echo Compilacion exitosa.
pause
