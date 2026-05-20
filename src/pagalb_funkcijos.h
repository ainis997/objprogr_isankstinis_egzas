#pragma once

#include <string>
#include <algorithm>
#include <exception>
#include <unordered_set>
#include <set>
#include <fstream>

#include "klases.h"

// funkcijos

std::ostream &operator<<(std::ostream &os, const std::set<unsigned int> &aibe);
std::string pakeist_skyryba_tarpais(std::string &zodis);
bool ar_url(std::string s);