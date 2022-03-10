#include "Banka.h"
#include "windows.h"

//test dosyası

int main(int argc, char const *argv[])
{
    SetConsoleOutputCP(65001);

    Banka banka = bankaOlustur();

        emirleriUygula(banka);

            return 0;
}
