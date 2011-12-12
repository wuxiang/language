#ifndef _TRACER_HPP_
#define _TRACER_HPP_
#include <iostream>

class SortTracer
{
    private:
        int value;
        int generation;
        static long n_created;
        static long n_destroyed;
        static long n_assigned;
        static long n_compared;
        static long n_max_live;

        static void  undate_max_live()
        {
            if (n_created - n_destroyed > n_max_live)
            {
                n_max_live = n_created - n_destroyed;
            }
        }

    public:
        static long creations()
        {
            return n_created;
        }

        static long destructions()
        {
            return n_destroyed;
        }

        static long assignments()
        {
            return n_compared;
        }

        static long comparisons()
        {
            return n_compared;
        }

        static long max_live()
        {
            return n_max_live;
        }

    public:
        SortTracer(int v = 0) : value(v), generation(1)
        {
            ++n_created;
            undate_max_live();
            std::cerr << "SortTracer#" << n_created << ", created generation" << generation \
                << "(total: " << n_created - n_destroyed << ')' << std::endl;
        }

        SortTracer(const SortTracer& b) : value(b.value), generation(b.generation + 1)
        {
            ++n_created;
            undate_max_live();
            std::cerr << "SortTracer#" << n_created << ", copied as generation " << generation \
                << " (total: " << n_created - n_destroyed << ')' << std::endl;
        }
        ~SortTracer()
        {
            ++n_destroyed;
            undate_max_live();
            std::cerr << "SortTracer generation " << generation << " destroyed (total: " \
                << n_created - n_destroyed << ')' << std::endl;
        }

        SortTracer& operator= (const SortTracer& b)
        {
            ++n_assigned;
            std::cerr << "SortTracer assignment #" << n_assigned << " (generation " << generation \
                << " = " <<  b.generation << ')' << std::endl;
            value = b.value;
            return *this;
        }

        // comparison
        friend bool operator < (const SortTracer& a, const SortTracer& b)
        {
            ++n_compared;
            std::cerr << "SortTracer comparison #" << n_compared << " (generation" << a.generation \
                << " < " << b.generation << ')' << std::endl;
            return a.value < b.value;
        }

        int val() const
        {
            return value;
        }
};
#endif //_TRACER_HPP_
