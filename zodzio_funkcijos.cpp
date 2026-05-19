#include "zodzio_funkcijos.h"

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

    return zodis;
}

bool ar_url(std::string s)
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