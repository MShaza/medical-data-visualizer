extends Camera3D

# Orbit camera — rotate around origin with mouse drag, zoom with scroll
var is_dragging = false
var last_mouse_pos = Vector2.ZERO
var orbit_distance = 3.0
var orbit_h_angle = 0.0   # horizontal angle in degrees
var orbit_v_angle = 20.0  # vertical angle in degrees

func _input(event):
	# Start/stop drag on right mouse button
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_RIGHT:
			is_dragging = event.pressed
			last_mouse_pos = event.position
		
		# Zoom with scroll wheel
		elif event.button_index == MOUSE_BUTTON_WHEEL_UP:
			orbit_distance = max(1.0, orbit_distance - 0.2)
			_update_camera()
		elif event.button_index == MOUSE_BUTTON_WHEEL_DOWN:
			orbit_distance = min(10.0, orbit_distance + 0.2)
			_update_camera()
	
	# Rotate while dragging
	if event is InputEventMouseMotion and is_dragging:
		var delta = event.position - last_mouse_pos
		orbit_h_angle -= delta.x * 0.5
		orbit_v_angle -= delta.y * 0.5
		orbit_v_angle = clamp(orbit_v_angle, -80.0, 80.0)
		last_mouse_pos = event.position
		_update_camera()

func _update_camera():
	# Convert spherical coordinates to cartesian
	var h_rad = deg_to_rad(orbit_h_angle)
	var v_rad = deg_to_rad(orbit_v_angle)
	
	position = Vector3(
		orbit_distance * cos(v_rad) * sin(h_rad),
		orbit_distance * sin(v_rad),
		orbit_distance * cos(v_rad) * cos(h_rad)
	)
	look_at(Vector3.ZERO, Vector3.UP)