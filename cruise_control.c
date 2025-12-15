#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#define MIN_CRUISE_SPEED 40
#define MAX_CRUISE_SPEED 180
#define SPEED_TOLERANCE 2


typedef struct {
    bool enabled;
    int target_speed;
    int current_speed;
    bool brake_pressed;
    bool clutch_pressed;
} CruiseControl;

void cruise_init(CruiseControl *cc) {
    cc->enabled = false;
    cc->target_speed = 0;
    cc->current_speed = 0;
    cc->brake_pressed = false;
    cc->clutch_pressed = false;
}

void cruise_update_speed(CruiseControl *cc, int speed) {
    cc->current_speed = speed;
}

void cruise_press_brake(CruiseControl *cc) {
    cc->brake_pressed = true;
    cc->enabled = false;
}

void cruise_press_clutch(CruiseControl *cc) {
    cc->clutch_pressed = true;
    cc->enabled = false;
}

void cruise_release_pedals(CruiseControl *cc) {
    cc->brake_pressed = false;
    cc->clutch_pressed = false;
}

bool cruise_enable(CruiseControl *cc, int target_speed) {

    if (cc->brake_pressed || cc->clutch_pressed) {
        return false;
    }

    if (target_speed < MIN_CRUISE_SPEED || target_speed > MAX_CRUISE_SPEED) {
        return false;
    }

    cc->enabled = true;
    cc->target_speed = target_speed;
    return true;
}

void cruise_disable(CruiseControl *cc) {
    cc->enabled = false;
}

int cruise_control_step(CruiseControl *cc) {

    if (!cc->enabled) {
        return cc->current_speed;
    }

    if (cc->brake_pressed || cc->clutch_pressed) {
        cc->enabled = false;
        return cc->current_speed;
    }

    if (cc->current_speed < cc->target_speed - SPEED_TOLERANCE) {
        return cc->current_speed + 1;
    }

    if (cc->current_speed > cc->target_speed + SPEED_TOLERANCE) {
        return cc->current_speed - 1;
    }

    return cc->current_speed;
}

void test_init_default_state() {
    CruiseControl cc;
    cruise_init(&cc);

    assert(cc.enabled == false);
    assert(cc.target_speed == 0);
    assert(cc.current_speed == 0);
    assert(cc.brake_pressed == false);
    assert(cc.clutch_pressed == false);
}

void test_enable_valid_speed() {
    CruiseControl cc;
    cruise_init(&cc);
    cruise_update_speed(&cc, 80);

    bool result = cruise_enable(&cc, 100);

    assert(result == true);
    assert(cc.enabled == true);
    assert(cc.target_speed == 100);
}

void test_enable_below_min_speed() {
    CruiseControl cc;
    cruise_init(&cc);

    bool result = cruise_enable(&cc, 30);

    assert(result == false);
    assert(cc.enabled == false);
}

void test_enable_above_max_speed() {
    CruiseControl cc;
    cruise_init(&cc);

    bool result = cruise_enable(&cc, 200);

    assert(result == false);
    assert(cc.enabled == false);
}

void test_cancel_by_brake() {
    CruiseControl cc;
    cruise_init(&cc);
    cruise_update_speed(&cc, 90);
    cruise_enable(&cc, 100);

    cruise_press_brake(&cc);
    cruise_control_step(&cc);

    assert(cc.enabled == false);
}

void test_cancel_by_clutch() {
    CruiseControl cc;
    cruise_init(&cc);
    cruise_update_speed(&cc, 90);
    cruise_enable(&cc, 100);

    cruise_press_clutch(&cc);
    cruise_control_step(&cc);

    assert(cc.enabled == false);
}

void test_speed_increase() {
    CruiseControl cc;
    cruise_init(&cc);
    cruise_update_speed(&cc, 90);
    cruise_enable(&cc, 100);

    int new_speed = cruise_control_step(&cc);

    assert(new_speed == 91);
}

void test_speed_decrease() {
    CruiseControl cc;
    cruise_init(&cc);
    cruise_update_speed(&cc, 110);
    cruise_enable(&cc, 100);

    int new_speed = cruise_control_step(&cc);

    assert(new_speed == 109);
}

void test_speed_within_tolerance() {
    CruiseControl cc;
    cruise_init(&cc);
    cruise_update_speed(&cc, 101);
    cruise_enable(&cc, 100);

    int new_speed = cruise_control_step(&cc);

    assert(new_speed == 101);
}

void test_enable_at_min_limit() {
    CruiseControl cc;
    cruise_init(&cc);

    bool result = cruise_enable(&cc, MIN_CRUISE_SPEED);

    assert(result == true);
    assert(cc.enabled == true);
}

void test_enable_at_max_limit() {
    CruiseControl cc;
    cruise_init(&cc);

    bool result = cruise_enable(&cc, MAX_CRUISE_SPEED);

    assert(result == true);
    assert(cc.enabled == true);
}

void test_speed_exact_lower_tolerance() {
    CruiseControl cc;
    cruise_init(&cc);
    cruise_update_speed(&cc, 98);
    cruise_enable(&cc, 100);

    int new_speed = cruise_control_step(&cc);

    assert(new_speed == 98);
}

void test_speed_exact_upper_tolerance() {
    CruiseControl cc;
    cruise_init(&cc);
    cruise_update_speed(&cc, 102);
    cruise_enable(&cc, 100);

    int new_speed = cruise_control_step(&cc);

    assert(new_speed == 102);
}

void test_speed_just_below_lower_tolerance() {
    CruiseControl cc;
    cruise_init(&cc);
    cruise_update_speed(&cc, 97);
    cruise_enable(&cc, 100);

    int new_speed = cruise_control_step(&cc);

    assert(new_speed == 98);
}

void test_speed_just_above_upper_tolerance() {
    CruiseControl cc;
    cruise_init(&cc);
    cruise_update_speed(&cc, 103);
    cruise_enable(&cc, 100);

    int new_speed = cruise_control_step(&cc);

    assert(new_speed == 102);
}

int main() {
    test_init_default_state();
    test_enable_valid_speed();
    test_enable_below_min_speed();
    test_enable_above_max_speed();
    test_cancel_by_brake();
    test_cancel_by_clutch();
    test_speed_increase();
    test_speed_decrease();
    test_speed_within_tolerance();

    // Testes de limit
//  test_enable_at_min_limit();
//  test_enable_at_max_limit();

//  Testes de tolerancia
//  test_speed_exact_lower_tolerance();
//  test_speed_exact_upper_tolerance();
//  test_speed_just_below_lower_tolerance();
//  test_speed_just_above_upper_tolerance();

    printf("Todos os testes do Cruise Control passaram com sucesso!");
    return 0;
}
