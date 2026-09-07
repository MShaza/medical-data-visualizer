#include "vessel.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/color.hpp>

using namespace godot;

Vessel::Vessel() {
    diameter = 5.0f;
    pressure = 80.0f;
    segment_id = 0;
}

Vessel::~Vessel() {}

void Vessel::_ready() {
    update_visuals();
}

void Vessel::update_visuals() {
    // Create a cylinder mesh sized by diameter
    Ref<CylinderMesh> mesh;
    mesh.instantiate();
    mesh->set_top_radius(diameter * 0.01f);
    mesh->set_bottom_radius(diameter * 0.01f);
    mesh->set_height(0.3f);
    set_mesh(mesh);

    // Color by pressure: low=blue, normal=green, high=red
    Ref<StandardMaterial3D> mat;
    mat.instantiate();

    if (pressure < 60.0f) {
        mat->set_albedo(Color(0.2f, 0.4f, 1.0f)); // blue
    } else if (pressure <= 100.0f) {
        mat->set_albedo(Color(0.2f, 0.9f, 0.3f)); // green
    } else {
        mat->set_albedo(Color(1.0f, 0.2f, 0.2f)); // red
    }

    set_surface_override_material(0, mat);
}

void Vessel::set_diameter(float d) {
    diameter = d;
    if (is_inside_tree()) update_visuals();
}

float Vessel::get_diameter() const { return diameter; }

void Vessel::set_pressure(float p) {
    pressure = p;
    if (is_inside_tree()) update_visuals();
}

float Vessel::get_pressure() const { return pressure; }

void Vessel::set_segment_id(int id) { segment_id = id; }
int Vessel::get_segment_id() const { return segment_id; }

void Vessel::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_diameter", "d"), &Vessel::set_diameter);
    ClassDB::bind_method(D_METHOD("get_diameter"), &Vessel::get_diameter);
    ClassDB::bind_method(D_METHOD("set_pressure", "p"), &Vessel::set_pressure);
    ClassDB::bind_method(D_METHOD("get_pressure"), &Vessel::get_pressure);
    ClassDB::bind_method(D_METHOD("set_segment_id", "id"), &Vessel::set_segment_id);
    ClassDB::bind_method(D_METHOD("get_segment_id"), &Vessel::get_segment_id);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "diameter"), "set_diameter", "get_diameter");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "pressure"), "set_pressure", "get_pressure");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "segment_id"), "set_segment_id", "get_segment_id");
}