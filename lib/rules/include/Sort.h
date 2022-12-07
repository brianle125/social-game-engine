#include <vector>
#include "IRule.h"
#include <ContentVariant>


class Sort final : public rules::IRule{
    public:
        Sort(std::string key);
        Sort(std::string key, std::string sortingKey);
        ~Sort() {}
        std::optional<std::vector<rules::IRule>> executeRule(GameModel model) override;

       // void Sort::ExecuteRule();

    private:
       // vector<dataVariant>& sortVector;
       std::string key;
       std::string sortingKey;
};