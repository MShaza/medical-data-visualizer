#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "vessel.hpp"

using namespace godot;

// Called when Godot loads your library
void initialize_medical_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    // Register your classes here — add more as we build them
    ClassDB::register_class<Vessel>();
}

// Called when Godot unloads your library
void uninitialize_medical_module(ModuleInitializationLevel p_level) {
    // cleanup if needed
}

// The actual entry point Godot calls — do not rename this
extern "C" {
GDExtensionBool GDE_EXPORT medical_library_init(
    GDExtensionInterfaceGetProcAddress p_get_proc_address,
    const GDExtensionClassLibraryPtr p_library,
    GDExtensionInitialization *r_initialization
) {
    godot::GDExtensionBinding::InitObject init_obj(
        p_get_proc_address, p_library, r_initialization
    );
    init_obj.register_initializer(initialize_medical_module);
    init_obj.register_terminator(uninitialize_medical_module);
    init_obj.set_minimum_library_initialization_level(
        MODULE_INITIALIZATION_LEVEL_SCENE
    );
    return init_obj.init();
}
}