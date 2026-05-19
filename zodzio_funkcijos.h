#pragma once

#include <string>
#include <algorithm>
#include <exception>
#include <unordered_set>
#include <fstream>

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

// funkcijos

std::string pakeist_skyryba_tarpais(std::string zodis);
bool ar_url(std::string s);