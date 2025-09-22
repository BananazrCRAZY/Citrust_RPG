#pragma once
#include "Status.h"
#include <vector>

using std::vector;

class StatusManager {
    vector<Status*> effects;
    vector<Status*> deleteThisEffects;

    const Status* getStatusSearch(int id, unsigned lower, unsigned upper);
    
    public:
        StatusManager();
        ~StatusManager();
        StatusManager(const StatusManager&) = delete;
        StatusManager& operator=(const StatusManager&) = delete;
        const Status* getStatus(int id);
};