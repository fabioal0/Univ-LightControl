/**
 * \file: lightControllSM.h
 *
 */
#pragma once

#include <stdint.h>

/* Light Controll State Machine states */
typedef enum { ManualMode, Dimmer, AutomaticSwitch, AutomaticAjust} lightControllState;

/* Data structure for the state machine */
typedef struct {
	lightControllState current_state;
	lightControllState initial_state;
} stateMachine;

/*
 * State machine execution
 */
void stateMachine_execute(stateMachine * state);

/*
 * Set initial state
 */
void stateMachine_init(stateMachine * state);

/*
 * Get current state
 */
uint32_t get_current_state(stateMachine * state);

/* State machine data structure */
extern stateMachine smLightControll;
