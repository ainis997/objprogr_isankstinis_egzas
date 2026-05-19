#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm> // remove_if ir t.t.
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <exception>
#include <format>

class Domenu_priesagos
{
public:
    const std::string domenu_priesagu_failo_pav = "domenu_priesagos.txt";
    std::unordered_set<std::string> domenu_priesagos;
    Domenu_priesagos()
    {
        std::ifstream domenu_priesagu_failas(domenu_priesagu_failo_pav);
        std::string eil;
        while (std::getline(domenu_priesagu_failas, eil))
        {
            domenu_priesagos.insert(eil);
        }
    }
};

bool ar_url(std::string s); // be šito, klasės metodai nefiksuoja friendinės ar_url funkcijos

class Tekstas
{
    std::string ivesties_failo_pav;
    std::unordered_map<std::string, unsigned int> zodziai;

public:
    Tekstas(std::string ivesties_failo_pav) : ivesties_failo_pav(ivesties_failo_pav) {}

    std::string pakeist_skyryba_tarpais(std::string zodis)
    {
        for (char &c : zodis)
        {
            if (std::ispunct(static_cast<unsigned char>(c))) // įskaitant '-', pvz. Tumas-Vaižgantas — tai gi du žodžiai
            {
                c = ' ';
            }
        }

        const std::string zenklai[] = {"„", "“", "–", "−", "—", "”", "“", "…"};
        for (const std::string &zenklas : zenklai)
        {
            size_t pos = zodis.find(zenklas);
            while (pos != std::string::npos)
            {
                zodis.replace(pos, zenklas.length(), zenklas.length(), ' ');
                pos = zodis.find(zenklas, pos + zenklas.length());
            }
        }

        // zodis.erase(std::remove_if(zodis.begin(), zodis.end(), [](unsigned char c)
        //                            { return std::ispunct(c) && c != '-'; }), // '-' netrinam, nes plg. Tumas-Vaižgantas, Lavoriškių-Nemenčinės
        //             zodis.end());

        // // likusių, utf-8 skyrybos ženklų valymas
        // const std::string zenklai[] = {"„", "“", "–", "”", "…"};
        // for (const std::string &zenklas : zenklai)
        // {
        //     size_t poz = zodis.find(zenklas);
        //     if (poz != std::string::npos) // jeigu rasta
        //     {
        //         zodis.erase(poz, zenklas.length());
        //     }
        // }

        return zodis;
    }

    friend bool ar_url(std::string s)
    {
        if (s.substr(0, 7) == "http://" || s.substr(0, 8) == "https://")
        {
            return true;
        }
        Domenu_priesagos d;
        if (d.domenu_priesagos.empty())
        {
            throw std::runtime_error("Nerastos URL domenų priesagos.");
        }

        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                       { return std::toupper(c); });
        for (const auto &priesaga : d.domenu_priesagos)
        {
            if (s.ends_with("." + priesaga))
            {
                return true;
            }
            if (s.find("." + priesaga + "/") != std::string::npos) // ne tik ends_with .xxx/, nes pvz. prusaspira.org/wirdeins
            {
                return true;
            }
        }
        return false;
    }

    void suskaityt_zodziai()
    {
        std::ifstream failas(ivesties_failo_pav);
        std::string eil;
        if (!failas.is_open())
        {
            throw std::runtime_error("Nepavyko atidaryti failo: " + ivesties_failo_pav);
        }

        unsigned int eil_num = 0;
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
                        zodziai[zodis2]++; // jei žodžio nėra, bus pridėtas naujas raktas su default int verte 0, ir po ++ jis taps 1; jei žodis yra, tsg bus ++'intas dab skaitiklis
                    }
                }
                else
                {
                    // jeigu url prasideda skyrybos ženklu, pašalinam jį (neturėtų gi)
                    if (std::ispunct(static_cast<unsigned char>(zodis.at(0))))
                    {
                        zodis = zodis.substr(1);
                    }
                    zodziai[zodis]++;
                }
            }
            ++eil_num;
        }
        failas.close();
    }

    void spausd_zodziu_statistika(std::string isvesties_failo_pav = "isvestis.txt")
    {
        std::ofstream isvesties_failas(isvesties_failo_pav);
        for (const auto &pora : zodziai)
        {
            if (pora.second > 1)
                isvesties_failas << std::format("{:<30}{:<10}\n", pora.first, pora.second); // < — kairėn; 30/10 — setw
            // isvesties_failas << std::left << std::setw(30) << pora.first << std::left << std::setw(10) << pora.second << '\n';
        }
        isvesties_failas.close();
    }

    // friend std::ostream &operator<<(std::ostream &os, const std::unordered_map<std::string, unsigned int> &zodziai)
    // {
    //     //
    // }
};

int main()
{
    Tekstas tekstas("tekstas.txt");
    tekstas.suskaityt_zodziai();
    tekstas.spausd_zodziu_statistika();
    return 0;
}