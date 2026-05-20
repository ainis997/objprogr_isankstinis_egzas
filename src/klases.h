#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <format>
#include <exception>
#include <iostream>

#include "pagalb_funkcijos.h"

class Zodzio_duomenys
{
public:
    unsigned int pasikartojimai;
    std::set<unsigned int> atveju_eilutes;
    Zodzio_duomenys() : pasikartojimai(1) {}
};

class Domenu_priesagos
{
public:
    const std::string domenu_priesagu_failo_pav = "domenu_priesagos.txt";
    std::unordered_set<std::string> domenu_priesagos;
    Domenu_priesagos()
    {
        std::ifstream domenu_priesagu_failas("src/" + domenu_priesagu_failo_pav);
        std::string eil;
        while (std::getline(domenu_priesagu_failas, eil))
        {
            domenu_priesagos.insert(eil);
        }
    }
};

class Tekstas
{
    std::string ivesties_failo_pav;
    std::unordered_map<std::string, Zodzio_duomenys> zodziai; // map, ne set, nes seto elementus redaguot nepatogu
    std::unordered_set<std::string> urlai;

public:
    Tekstas(std::string ivesties_failo_pav) : ivesties_failo_pav("tekstai/" + ivesties_failo_pav) {}

    void suskaityt_zodziai();

    void spausd_zodziu_statistika(std::string isvesties_failo_pav = "zodziai_su_ju_pasikartojimu_sk.txt");

    void spausd_zodziu_atveju_lentele(std::string isvesties_failo_pav = "lentele.txt");

    void spausd_urlus(std::string isvesties_failo_pav = "urlai.txt");
};