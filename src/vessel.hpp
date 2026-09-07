#ifndef VESSEL_HPP
#define VESSEL_HPP

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/cylinder_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

class Vessel : public MeshInstance3D {
    GDCLASS(Vessel, MeshInstance3D)

private:
    float diameter;      // vessel diameter in mm
    float pressure;      // blood pressure value
    int segment_id;      // which segment this is

    void update_visuals(); // redraws mesh based on data

public:
    Vessel();
    ~Vessel();

    void _ready() override;

    // Setters & Getters — callable from Godot editor
    void set_diameter(float d);
    float get_diameter() const;

    void set_pressure(float p);
    float get_pressure() const;

    void set_segment_id(int id);
    int get_segment_id() const;

    static void _bind_methods();
};

} // namespace godot

#endif