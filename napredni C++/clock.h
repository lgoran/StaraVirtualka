#include <chrono>

// Klasa clock koja pojednostavljuje mjerenje vremena izvršavanja programa.
// Vrijeme se može mjeriti samo u sekundama, milisekundama ili mikrosekundama.
// Sat se pokreće u konstruktoru ili pozivom metode start(). Zaustavlja se 
// pozivom metode stop() koja vraća proteklo vrijeme od posljednjeg poziva 
// start() metode u traženim jedinicama.
class Clock{
    public:
        enum Interval{sec, millisec, microsec};
        Clock(){start();}
        // Pokreni sat.
        void start();
        // Zaustavi sat i vrati proteklo vrijeme u unit jedinicama.
        double stop(Interval unit);
    private:
        std::chrono::high_resolution_clock mClock;
        std::chrono::time_point<std::chrono::high_resolution_clock> begin;
        std::chrono::time_point<std::chrono::high_resolution_clock> end;
};

void Clock::start()
{
    begin=mClock.now();
}
double Clock::stop(Interval unit)
{
    end=mClock.now();
    if(unit==Interval::millisec)
        return std::chrono::duration<double, std::milli>(end-begin).count();
    else if(unit== Interval::microsec)
        return std::chrono::duration<double, std::micro>(end-begin).count();
    else 
        return std::chrono::duration<double, std::ratio<1L,1L>>(end-begin).count();
}

// Primjer upotrebe:
//  
//    clock.start();
//    double sum = std::accumulate(niz, niz+SIZE, 0.0);
//    auto time = clock.stop(Clock::microsec);
//    std::cout << "ser. sum = " << std::setprecision(10) << sum << ", time = " << time << " us" << std::endl;

