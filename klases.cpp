#include "klases.h"

void Tekstas::suskaityt_zodziai()
{
    std::ifstream failas(ivesties_failo_pav);
    std::string eil;
    if (!failas.is_open())
    {
        throw std::runtime_error("Nepavyko atidaryti failo: " + ivesties_failo_pav);
    }

    unsigned int eil_num = 1;
    while (std::getline(failas, eil))
    {
        std::istringstream sr(eil);
        std::string zodis;
        while (sr >> zodis)
        {
            // minimalūs pataisymai (pvz. gale tašką išimt), kad netrukdytų atpažint url'ų
            if (std::ispunct(zodis.at(zodis.length() - 1)))
            {
                zodis = zodis.substr(0, zodis.length() - 1);
            }
            else if (std::ispunct(zodis.at(0))) // maz kas
            {
                zodis = zodis.substr(1);
            }

            if (!ar_url(zodis))
            {
                std::string zodis_be_skyrybos = pakeist_skyryba_tarpais(zodis);
                std::istringstream ss(zodis_be_skyrybos);
                std::string zodis2;
                while (ss >> zodis2) // atsikratom sukurtų tarpų (jeigu jų buvo; jeigu ne, nieks nepakis)
                {
                    ///////////////////////////////////////////
                    if (zodziai.contains(zodis2))
                    {
                        zodziai[zodis2].pasikartojimai++;
                        zodziai[zodis2].atveju_eilutes.insert(eil_num);
                    }
                    else
                    {
                        Zodzio_duomenys zd;
                        zodziai.insert({zodis2, zd});
                    }
                }
            }
            else
            {
                // jeigu url prasideda skyrybos ženklu, pašalinam jį (neturėtų gi)
                if (std::ispunct(static_cast<unsigned char>(zodis.at(0))))
                {
                    zodis = zodis.substr(1);
                }

                urlai.insert(zodis); // kaupiam atskirai URLus; jeigu toks URLas jau yra, unordered_set tsg nepakis
                if (zodziai.contains(zodis))
                {
                    zodziai[zodis].pasikartojimai++;
                    zodziai[zodis].atveju_eilutes.insert(eil_num);
                }
                else
                {
                    Zodzio_duomenys zd;
                    zodziai.insert({zodis, zd});
                }
            }
        }
        ++eil_num;
    }
    failas.close();
}

void Tekstas::spausd_zodziu_statistika(std::string isvesties_failo_pav)
{
    std::ofstream isvesties_failas(isvesties_failo_pav);
    for (const auto &pora : zodziai)
    {
        if (pora.second.pasikartojimai > 1)
            isvesties_failas << std::format("{:<30}{:<20}\n", pora.first, pora.second.pasikartojimai); // < — kairėn; 30/10 — setw
        // isvesties_failas << std::left << std::setw(30) << pora.first << std::left << std::setw(10) << pora.second << '\n';
    }
    isvesties_failas.close();
}

void Tekstas::spausd_zodziu_atveju_lentele(std::string isvesties_failo_pav)
{
    std::ofstream isvesties_failas(isvesties_failo_pav);
    isvesties_failas << std::format("{:<30}{:<20}Atvejų eilutės\n", "Žodis", "Atvejų sk.");
    for (const auto &pora : zodziai)
    {
        if (pora.second.pasikartojimai > 1)
        {
            isvesties_failas << std::format("{:<30}{:<20}", pora.first, pora.second.pasikartojimai);
            isvesties_failas << pora.second.atveju_eilutes << '\n';
        }
    }
}

void Tekstas::spausd_urlus(std::string isvesties_failo_pav)
{
    std::ofstream isvesties_failas(isvesties_failo_pav);
    for (const auto &url : urlai)
    {
        isvesties_failas << url << '\n';
    }
}