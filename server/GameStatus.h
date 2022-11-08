//
// Created by Yiwen Wang on 2022-11-06.
//

#ifndef SOCIAL_GAMING_GAMESTATUS_H
#define SOCIAL_GAMING_GAMESTATUS_H
#include <string>
#include <optional>

class GameStatus {
private:
    std::string value;
public:
    static std::optional<GameStatus> try_parse(std::string value);

    GameStatus(const std::string&);
    GameStatus(std::string&&);
    std::string get_value() const;
    bool operator== (const GameStatus &) const;

    const static GameStatus not_started;
    const static GameStatus running;
    const static GameStatus paused;
    const static GameStatus terminated;
    const static GameStatus error;
};
#endif //SOCIAL_GAMING_GAMESTATUS_H
