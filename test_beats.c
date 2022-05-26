// Assignment 2 20T1 COMP1511: CS bEats
// test_beats.c
//
// This program was written by CHAN WOO BAEK (z5259628)
// on 25/04/2020
//
// Version 1.0.0: Assignment released.
#include <stdio.h>
#include <stdlib.h>

#include "test_beats.h"
#include "beats.h"


// Test function for `add_note_to_beat`
int test_add_note_to_beat(void) {
    // Test 1: Rejecting negative inputs.
    Beat test_beat = create_beat();
    if (add_note_to_beat(test_beat, -1, -1) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, -1, 0) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 1, -1) != INVALID_KEY) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Rejecting same inputs   
    add_note_to_beat(test_beat, 1, 1);
    if (add_note_to_beat(test_beat, 1, 1) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 3: Rejecting lower note inputs
    add_note_to_beat(test_beat, 3, 1);
    if (add_note_to_beat(test_beat, 2, 1) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    return MEETS_SPEC;
}

// Test function for `count_notes_in_octave`
int test_count_notes_in_octave(void){
    // Test 1: Counting invalid octaves.
    Beat test_beat = create_beat();
    add_note_to_beat(test_beat, 1, 1);
    if (count_notes_in_octave(test_beat, -1) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 11) != 0) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Not counting a valid octave
    if (count_notes_in_octave(test_beat, 1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: If the count is not accurate
    add_note_to_beat(test_beat, 1, 5);
    add_note_to_beat(test_beat, 1, 8);
    if (count_notes_in_octave(test_beat, 1) != 3) {
        return DOES_NOT_MEET_SPEC;
    }
    return MEETS_SPEC;
}

// Test function for `add_beat_to_track`
int test_add_beat_to_track(void){
    // Test 1: If the beats are added into the track.
    Track test_track = create_track();
    
    Beat test_beat = create_beat();
    add_note_to_beat(test_beat, 1, 1);
    add_beat_to_track(test_track, test_beat);
    
    Beat test_beat2 = create_beat();
    add_note_to_beat(test_beat2, 2, 1);
    add_beat_to_track(test_track, test_beat2);
    
    
    if (count_beats_left_in_track(test_track) != 2) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 2: If a beat is selected, it correctly counts the amount of beats
    //         after the selected beat.

    select_next_beat(test_track);
    if (count_beats_left_in_track(test_track) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 3: If the selected beat is the last beat, it counts zero
    Beat test_beat3 = create_beat();
    add_note_to_beat(test_beat3, 1, 6);
    add_beat_to_track(test_track, test_beat3);
    select_next_beat(test_track);
    select_next_beat(test_track);
    if (count_beats_left_in_track(test_track) != 0) {
        return DOES_NOT_MEET_SPEC;
    }

    return MEETS_SPEC;
}

// Test function for `remove_selected_beat`
int test_remove_selected_beat(void) {
    Track test_track = create_track();
    
    Beat test_beat = create_beat();
    add_note_to_beat(test_beat, 2, 3);    
    add_beat_to_track(test_track, test_beat);
    
    Beat test_beat2 = create_beat();
    add_note_to_beat(test_beat2, 3, 4);
    add_beat_to_track(test_track, test_beat2);
    
    //Test 1: If there is no beat selected, function should do nothing
    remove_selected_beat(test_track);
    if (count_beats_left_in_track(test_track) != 2) {
        return DOES_NOT_MEET_SPEC;
    }    
    
    // Test 2: If the first selected beat is removed
    select_next_beat(test_track);
    remove_selected_beat(test_track);
    
    if (count_beats_left_in_track(test_track) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 3: If we can remove a beat from the middle of the track
    Beat test_beat3 = create_beat();
    add_note_to_beat(test_beat3, 3, 6);
    add_beat_to_track(test_track, test_beat3);
    
    Beat test_beat4 = create_beat();
    add_note_to_beat(test_beat4, 4, 5);
    add_beat_to_track(test_track, test_beat4);
    
    Beat test_beat5 = create_beat();
    add_note_to_beat(test_beat5, 4, 7);
    add_beat_to_track(test_track, test_beat5);
    
    select_next_beat(test_track);
    remove_selected_beat(test_track);
   
    if (count_beats_left_in_track(test_track) != 1) {
        return DOES_NOT_MEET_SPEC;
    }



    return MEETS_SPEC;
}

// Test function for `add_musical_note_to_beat`
int test_add_musical_note_to_beat(void){
    // Test 1: If the musical note is added
    Beat test_beat = create_beat();
    char musical_notation[10];
    musical_notation[0] = 48;
    musical_notation[1] = 'F';
    
    add_musical_note_to_beat(test_beat, musical_notation);
    if (count_notes_in_octave(test_beat, 0) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    

    // Test 2: If a musical note with # is added 
    musical_notation[0] = 57;
    musical_notation[1] = 'G';
    musical_notation[2] = '#';
    add_musical_note_to_beat(test_beat, musical_notation);
    
    if (count_notes_in_octave(test_beat, 0) != 2) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: If the function can recognise an invalid musical note
    musical_notation[0] = 'A';
    musical_notation[1] = 'G';
    if (add_musical_note_to_beat(test_beat, musical_notation) != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    return MEETS_SPEC;
}
