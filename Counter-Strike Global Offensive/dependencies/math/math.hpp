#pragma once

namespace math {
	constexpr float pi = 3.1415926535897932384f;
	constexpr float pi_2 = pi * 2.f;

	void correct_movement(vec3_t old_angles, c_usercmd* cmd, float old_forwardmove, float old_sidemove);
	vec3_t calculate_angle(vec3_t& a, vec3_t& b);
	void sin_cos(float r, float* s, float* c);
	vec3_t angle_vector(vec3_t angle);
	void transform_vector(vec3_t&, matrix_t&, vec3_t&);
	void vector_angles(vec3_t&, vec3_t&);
	void angle_vectors(vec3_t&, vec3_t*, vec3_t*, vec3_t*);
	vec3_t vector_add(vec3_t&, vec3_t&);
	vec3_t vector_subtract(vec3_t&, vec3_t&);
	vec3_t vector_multiply(vec3_t&, vec3_t&);
	vec3_t vector_divide(vec3_t&, vec3_t&);
	bool screen_transform(const vec3_t& point, vec3_t& screen);
	bool world_to_screen(const vec3_t& origin, vec3_t& screen);
	float rad_to_deg(float val);
	float deg_to_rad(float val);
	float NormalizeYaw(float angle);
};
