#pragma once

class Stat {
    int base;
    int additional;
    int total;

    public:
        Stat(int initialBase) : base(initialBase), total(initialBase) {}
        void add(int change) {
            if (total <= 0) return;
            additional += change;
            total += change;
            if (total < 0) {
                int difference = -1 * total;
                additional += difference;
                total += difference;
            }
        }
        void removeAdd() {
            total = base;
            additional = 0;
        }
        void addBase(int addBase) {
            total -= base;
            base += addBase;
            total += base;
        }
        int getBase() const { return base; }
        int getTotal() const { return total; }
};