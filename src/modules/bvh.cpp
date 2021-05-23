#include "bvh.h"
#include "aabb.h"

namespace ray_lib
{
    // todo move these to a utility class
    inline double random_double() {
        // Returns a random real in [0,1).
        return rand() / (RAND_MAX + 1.0);
    }

    inline double random_double(double min, double max) {
        // Returns a random real in [min,max).
        return min + (max-min)*random_double();
    }
    inline int random_int(int min, int max) {
        // Returns a random integer in [min,max].
        return static_cast<int>(random_double(min, max+1));
    }

    inline bool box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis)
    {
        aabb box_a;
        aabb box_b;

        if (!a->bounding_box( &box_a) || !b->bounding_box( &box_b))
            std::cerr << "No bounding box in bvh_node constructor.\n";

        return box_a.min()[axis] < box_b.min()[axis];
    }

    bool box_x_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
    {
        return box_compare(a, b, 0);
    }

    bool box_y_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
    {
        return box_compare(a, b, 1);
    }

    bool box_z_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
    {
        return box_compare(a, b, 2);
    }

    bvh_node::bvh_node(
        const std::vector<std::shared_ptr<Hittable>> &src_objects,
        size_t start, size_t end)
    {
        auto objects = src_objects; // Create a modifiable array of the source scene objects

        int axis = random_int(0, 2);
        auto comparator = (axis == 0)   ? box_x_compare
                          : (axis == 1) ? box_y_compare
                                        : box_z_compare;

        size_t object_span = end - start;

        if (object_span == 1)
        {
            left = right = objects[start];
        }
        else if (object_span == 2)
        {
            if (comparator(objects[start], objects[start + 1]))
            {
                left = objects[start];
                right = objects[start + 1];
            }
            else
            {
                left = objects[start + 1];
                right = objects[start];
            }
        }
        else
        {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);

            auto mid = start + object_span / 2;
        left = std::make_shared<bvh_node>(objects, start, mid);
        right = std::make_shared<bvh_node>(objects, mid, end);
        }

        aabb box_left, box_right;

        if (!left->bounding_box(&box_left) || !right->bounding_box(&box_right))
            std::cerr << "No bounding box in bvh_node constructor.\n";

        box = surrounding_box(box_left, box_right);
    }

    bool bvh_node::intersects(const Ray &r, double t_min, double t_max, Intersection *rec) const
    {
        if (!box.hit(r, t_min, t_max))
            return false;

        bool hit_left = left->intersects(r, t_min, t_max, rec);
        bool hit_right = right->intersects(r, t_min, hit_left ? rec->t() : t_max, rec);

        return hit_left || hit_right;
    }

    bool bvh_node::bounding_box(aabb *output_box) const
    {
        *output_box = box;
        return true;
    }
} //namespace ray_lib
