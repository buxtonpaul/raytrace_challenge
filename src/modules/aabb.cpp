#include "aabb.h"
#include "rays.h"

namespace ray_lib{
bool  aabb::hit(const Ray& r, double t_min, double t_max) const {
            for (int a = 0; a < 3; a++) {
                auto t0 = fmin((minimum[a] - r.Origin()[a]) / r.Direction()[a],
                               (maximum[a] - r.Origin()[a]) / r.Direction()[a]);
                auto t1 = fmax((minimum[a] - r.Origin()[a]) / r.Direction()[a],
                               (maximum[a] - r.Origin()[a]) / r.Direction()[a]);
                t_min = fmax(t0, t_min);
                t_max = fmin(t1, t_max);
                if (t_max <= t_min)
                    return false;
            }
            return true;
        }


}