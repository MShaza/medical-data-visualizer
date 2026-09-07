extends Node3D

# Fake medical data — 5 vessel segments
# Each entry is [diameter_mm, pressure_mmHg]
var vessel_data = [
	[3.5, 55.0],   # segment 0 — narrow, low pressure (blue)
	[5.0, 80.0],   # segment 1 — normal (green)
	[6.2, 95.0],   # segment 2 — wide, normal (green)
	[4.1, 115.0],  # segment 3 — high pressure (red)
	[5.8, 78.0],   # segment 4 — normal (green)
]

var selected_vessel = null
var info_label

func _ready():
	# Get reference to UI label
	info_label = $UI/InfoLabel
	
	# Spawn vessel segments in a line
	for i in range(vessel_data.size()):
		var vessel = Vessel.new()
		vessel.segment_id = i
		vessel.diameter = vessel_data[i][0]
		vessel.pressure = vessel_data[i][1]
		
		# Position each segment along X axis
		vessel.position = Vector3(i * 0.4 - 0.8, 0, 0)
		
		# Rotate so cylinders are horizontal
		vessel.rotation_degrees = Vector3(90, 0, 0)
		
		add_child(vessel)
	
	info_label.text = "Click a vessel segment to see data"

func _input(event):
	if event is InputEventMouseButton:
		if event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
			_try_select_vessel(event.position)

func _try_select_vessel(mouse_pos):
	# Raycast from camera into 3D scene
	var camera = $Camera3D
	var from = camera.project_ray_origin(mouse_pos)
	var to = from + camera.project_ray_normal(mouse_pos) * 100.0
	
	var space = get_world_3d().direct_space_state
	var query = PhysicsRayQueryParameters3D.create(from, to)
	var result = space.intersect_ray(query)
	
	if result and result.collider:
		var parent = result.collider.get_parent()
		if parent is Vessel:
			_show_vessel_info(parent)
	else:
		info_label.text = "Click a vessel segment to see data"

func _show_vessel_info(vessel):
	var status = "NORMAL"
	if vessel.pressure < 60.0:
		status = "LOW"
	elif vessel.pressure > 100.0:
		status = "HIGH"
	
	info_label.text = (
		"Segment %d\n" % vessel.segment_id +
		"Diameter: %.1f mm\n" % vessel.diameter +
		"Pressure: %.0f mmHg\n" % vessel.pressure +
		"Status: %s" % status
	)