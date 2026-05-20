#include <iostream>
#include <fstream>
#include <string>
#include <exception>

#include "klases.h"

int main()
{
    std::cout << "Tekstu aplanko failai:\n";
    system("dir tekstai");
    std::cout << "Iveskite norimo nuskaityti teksto failo pilna pavadinima:\n";
    std::string tekstfailo_pav;
    while (true)
    {
        std::getline(std::cin, tekstfailo_pav);
        try
        {
            std::ifstream tekstfailas("tekstai/" + tekstfailo_pav);
            if (!tekstfailas.is_open())
            {
                throw std::runtime_error("Tokio pavadinimo failas nerastas.");
            }
            break;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Bandykite dar karta:\n";
        }
    }
    Tekstas tekstas(tekstfailo_pav);
    tekstas.suskaityt_zodziai();

    tekstas.spausd_zodziu_statistika();
    std::cout << "Isvestas failas su zodziais ir ju pasikartojimu sk.\n";

    tekstas.spausd_zodziu_atveju_lentele();
    std::cout << "Isvestas failas su zodziu, ju pasikartojimu sk. ir eiluciu lentele.\n";

    tekstas.spausd_urlus();
    std::cout << "Isvestas failas su teksto URL'ais.\n";

    return 0;
}