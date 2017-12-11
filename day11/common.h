#include <utility>
#include <unordered_map>
#include <algorithm>

template <typename T, typename U>                                                   
void operator+=(std::pair<T, U> &l,const std::pair<T, U> &r) {   
    l.first += r.first;
    l.second += r.second;
}

template <typename key_t, typename value_t>
bool has_key(const std::unordered_map<key_t, value_t> &map, const key_t key) {
    return map.find(key) != map.end();
}

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
