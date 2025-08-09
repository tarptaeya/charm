#include "charm_utils.h"

namespace charm {

namespace utils {

    std::vector<std::string> split(const std::string& str, char delim)
    {
        std::vector<std::string> ans;
        std::string token;
        for (int i = 0; i < str.length(); ++i) {
            if (str[i] == delim) {
                ans.push_back(token);
                token = "";
            } else {
                token += str[i];
            }
        }

        ans.push_back(token);
        return ans;
    }

}

}