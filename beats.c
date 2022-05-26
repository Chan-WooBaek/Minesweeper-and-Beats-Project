// Assignment 2 20T1 COMP1511: CS bEats
// beats.c
//
// This program was written by CHAN WOO BAEK (z5259628)
// on 25/04/2020
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Fix default return value of add_musical_note_to_beat.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Add any extra #includes your code needs here.
#include <string.h>

#include "beats.h"

// Add your own #defines here.

////////////////////////////////////////////////////////////////////////

// You don't have to use the provided struct track, you are free to
// make your own struct instead.
// If you use the provided struct track, you will have to add fields
// to store other information.

struct track {
    struct beat *head;
    struct beat *current;
};

// You don't have to use the provided struct beat, you are free to
// make your own struct instead.
// If you use the provided struct beat, you may add fields
// to it to store other information.

struct beat {
    // You may choose to add or change fields in this struct.
    struct note *notes;
    struct beat *next;
};

// You don't have to use the provided struct note, you are free to
// make your own struct instead.
// If you use the provided struct note, you add fields
// to it to store other information.

struct note {
    // You may choose to add or change fields in this struct.
    int octave;
    int key;
    struct note *next;
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////

// Add prototypes for any extra functions you create here.
int word_to_num(char word); 

// Return a malloced Beat with fields initialized.
Beat create_beat(void) {
    Beat new_beat = malloc(sizeof(struct beat));
    assert(new_beat != NULL);

    new_beat->next = NULL;
    new_beat->notes = NULL;

    // You do not need to change this function, unless you change
    // the implementation of struct beat.

    return new_beat;
}

// You need to implement the following functions.
// You can find descriptions of what each function should do in beats.h

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a note to the end of a beat.
int add_note_to_beat(Beat beat, int octave, int key) {
    //Checking if the octave and key is valid.
    if (octave <= -1 || octave >= 10) {
        return INVALID_OCTAVE;
    } else if (key <= -1 || key >= 12) {
        return INVALID_KEY;
    }
    
    //Checking if the note is higher than the previous.
    struct note *test = beat->notes;
    if (test != NULL) {
        //Looping until the last note.
        while (test->next != NULL) {
            test = test->next;
        }
        //Checking if the last note in the beat is higher than the one given.
        if (test->octave > octave) {
            return NOT_HIGHEST_NOTE;
            
        } else if (test->octave == octave && test->key == key) {
            return NOT_HIGHEST_NOTE;
            
        } else if (test->octave == octave && test->key > key) {
            return NOT_HIGHEST_NOTE;
            
        }
    }

    
    //Adding the note
    struct note *add = malloc(sizeof(struct note));
    add->octave = octave;
    add->key = key;
    add->next = NULL;
    
    struct note *reset = beat->notes;
    
    //If there were no previously existing notes in the beat.
    if (beat->notes == NULL) {
        beat->notes = add;
        return VALID_NOTE;
    } else if (beat->notes != NULL) {
        //Travelling to the last linked list beat->notes .
        while (beat->notes->next != NULL) {
            beat->notes = beat->notes->next;
        }
        //Adding the note to the end.
        beat->notes->next = add;
    }
    
    //Resetting beat->notes back to the original head.
    beat->notes = reset;
    
    return VALID_NOTE;
}

// Print the contents of a beat.
void print_beat(Beat beat) {
    struct note *temp = beat->notes;
    //Looping until there is no more linked lists left.
    while (temp != NULL) {
        //Checking whether to add 0 before the key or not.
        if (temp->key > 9) {
            printf("%d %d", temp->octave, temp->key);
        } else if (temp->key < 10) {
            printf("%d 0%d", temp->octave, temp->key);
        }
        //Checking if the note is the last one when printing " | ".
        if (temp->next != NULL) {
            printf(" | ");
        }
        temp = temp->next;
    }
    printf("\n");
    return;
}

// Count the number of notes in a beat that are in a given octave.
int count_notes_in_octave(Beat beat, int octave) {
    struct note *temp = beat->notes;
    int counter = 0;
    //Looping until there is no more linked lists left.
    while (temp != NULL) {
        //Checking whether the current linked list has the same
        //octave as the given one to check it against.
        if (temp->octave == octave) {
            counter++;
        }
        temp = temp->next;
    }
    return counter;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Return a malloced track with fields initialized.
Track create_track(void) {
    // Note: there is no fprintf in this function, as the
    // Stage 1 autotests call create_track but expect it to return NULL
    // (so this function should do nothing in Stage 1).
    
    
    //Creating a linked list of the new track which has the capability to 
    //store the selected beat and the head beat
    struct track *new_track = malloc(sizeof(struct track));
    new_track->head = NULL;
    new_track->current = NULL;
    return new_track;
}

// Add a beat after the current beat in a track.
void add_beat_to_track(Track track, Beat beat) {
    struct beat *reset = track->head;
    //If there is currently no selected beat.
    if (track->current == NULL) {
        //If there are no other beats in the track, add new beat to track.
        if (track->head == NULL) {
            track->head = beat;
        } 
        //If there is at least one other beat in the track.
        //Make the new beat the head followed by the previous head.
        else if (track->head != NULL) {
            track->head = beat;
            track->head->next = reset;     
        }
        
    } 
    //If there is a currently selected beat.
    else if (track->current != NULL) {
        //If there is no beat after the selected beat,
        //the beat after the selected beat is the new beat.
        if (track->current->next == NULL) {
            track->current->next = beat;
        } 
        //If there is a beat after the selected beat,
        //insert the new beat between the selected beat and the beat that was
        //previously the beat after the selected beat.
        else if (track->current->next != NULL) {
            beat->next = track->current->next;
            track->current->next = beat;
        }
        
    }
    return;
}

// Set a track's current beat to the next beat.
int select_next_beat(Track track) {
    struct track *temp = track;
    //If there are beats existing in the track and no beat selected.
    if (temp->current == NULL && temp->head != NULL) {
        track->current = track->head;
        return TRACK_PLAYING;
    }
    //If a beat is selected and it is also the last beat.
    if (temp->current != NULL && temp->current->next == NULL) {
        temp->current = NULL;
        return TRACK_STOPPED;
    }
    //If a beat is selected and it is not the last beat.
    if (temp->current != NULL && temp->current->next != NULL) {
        temp->current = temp->current->next;
        return TRACK_PLAYING;
    }
    return TRACK_STOPPED;
    
}

// Print the contents of a track.
void print_track(Track track) {
    int counter = 1;
    struct track *temp = track;
    //If there are no beats in the track.
    if (temp->head == NULL) {
        return;
    }
    struct beat *reset_head = track->head;

    //Looping through every linked list in the track.
    while (temp->head != NULL) {
        //If the beat we are currently on is the selected beat.
        if (temp->current == temp->head) {
            printf(">");
        } else (printf(" "));
        printf("[%d] ",counter);
        //Within the beat we are currently on,
        //print all the notes.
        print_beat(temp->head);
        counter++;
        temp->head = temp->head->next;
    }
    temp->head = reset_head;
    return;
}

// Count beats after the current beat in a track.
int count_beats_left_in_track(Track track) {
    int counter = 0;
    struct track *clone = track;
    struct beat *reset = track->head;
    //If there is no selected beat.
    if (clone->current == NULL) {
        //Looping through the entire linked list of track
        //count the no. of beats.
        while (clone->head != NULL) {
            counter++;
            clone->head = clone->head->next;
        }
        clone->head = reset;
    }
    //If there is a selected beat.
    if (clone->current != NULL) {
        counter = -1;
        //Let the head of track be the selected list.
        clone->head = clone->current;
        //Looping through the entire linked list.
        while (clone->head != NULL) {
            counter++;
            clone->head = clone->head->next;
        }
        clone->head = reset;
    }
    return counter;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

// Free the memory of a beat, and any memory it points to.
void free_beat(Beat beat) {
    // Note: there is no printf in this function, as the
    // Stage 1 & 2 autotests call free_beat but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1 & 2, rather than exit).
    //Do nothing if there is no beat.
    if (beat == NULL) {
        return;
    }
    struct note *store = beat->notes;
    //Looping and removing until there are no notes left.
    while (store != NULL) {
        struct note *temp = store; 
        store = store->next;
        free(temp);
    }
    //Removing the linked list beat.
    free(beat);
}

// Free the memory of a track, and any memory it points to.
void free_track(Track track) {
    // Note: there is no printf in this function, as the
    // Stage 1 & 2 autotests call free_track but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1 & 2, rather than print an error).
    struct beat *store = track->head;
    struct beat *prev = track->head;
    //Looping and removing until there are no beats left.
    while (prev != NULL) {
        //Storing the next beat to be removed.
        store = prev->next;
        //Freeing the beat we are currently on.
        free_beat(prev);
        //Setting the next beat to be removed as the beat we are currently on.
        prev = store;
    }
    //Removing the linked list track.
    free(track);
}

// Remove the currently selected beat from a track.
int remove_selected_beat(Track track) {
    //If there is a beat.
    if (track->head != NULL) {
        //If there is no selected beat.
        if (track->current == NULL) {
            return TRACK_STOPPED;
        } 
        //If there is a selected beat.
        else if (track->current != NULL) {
            struct beat *temp = track->head;
            struct beat *prev = NULL;
            //If selected beat is at the end of the list.
            if (track->current->next == NULL) {
                //If it is also the head of the list.
                if (track->head == track->current) {               
                    track->head = track->head->next;
                } 
                //If it is in the middle of the list.
                else {
                    while (temp != track->current) {
                        prev = temp;
                        temp = temp->next;
                    }
                    prev->next = temp->next; 
                }
                track->current = track->current->next;
                free_beat(temp);
                if (track->current != NULL) {
                    return TRACK_PLAYING;
                }
            } 
            //If the selected beat is not at the end of the list.
            else {
                
                //If it is also the head of the list.
                if (track->head == track->current) {               
                    track->head = track->head->next;
                } 
                //If it is in the middle of the list.
                else {
                    while (temp != track->current) {
                        prev = temp;
                        temp = temp->next;
                    }
                }
                
                //If the selected beat was the head of the list.
                if (prev == NULL) {
                    prev = temp;
                }
                //If the selected beat was the middle of the list.
                else if (prev != NULL) {
                    prev->next = temp->next;
                }
                
                //Moving the selected beat to the next beat.
                track->current = track->current->next;
                //Freeing the previous selected beat.
                free_beat(temp);
                //Checking whether the beat removed was the last beat.
                if (track->current != NULL) {
                    return TRACK_PLAYING;
                }
            }
        }
    }
    

    
    return TRACK_STOPPED;
}
////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add note to beat, given its 'musical notation'.
int add_musical_note_to_beat(Beat beat, char *musical_notation) {
    //Checking if there is a musical_notation to add or not.
    if (musical_notation == NULL) {
        return INVALID_MUSICAL_NOTE;
    }
    
    
    //Processing given musical note into numerals.
    
    //Creating a string for the musical notation.
    char string[strlen(musical_notation) + 1];
    strcpy(string, musical_notation);
    
    int count = 0;
    char octave = 's';
    char key = 's';
    int sharps = 0;
    int switch1 = 0;
    //Looping until we have reached the end of the string.
    while (string[count] != '\0') {
        //At the start of the string,
        //the first given char is the octave,
        //the following char is the key.
        if (count == 0) {
            octave = string[count];
            key = string[count + 1];
            switch1 = 1;
        } 
        //When switch1 = 1, we are on the key component of the string,
        //We use this if statement to skip this array so that the next if
        //statement will not recognise the key string 
        //and return INVALID_MUSICAL_NOTE.
        else if (switch1 == 1) {
            switch1++;
            
        } 
        //After the octave and key component of the char array string, while the
        //remaining inputs are #'s, add to the counter 'sharps'.
        else {
            if (string[count] != '#') {
                return INVALID_MUSICAL_NOTE;
            }
            sharps++;
        }
        
        count++;
    }
    
    //Convert the given char input of the octave into its numerical value.
    int finalOctave = octave - 48;
    
    //Checking if the given octave is within the permitted range.
    if (finalOctave > 9 || finalOctave < 0) {
        return INVALID_MUSICAL_NOTE;
    }
    //Checking if the given key is within the permitted range.
    if (word_to_num(key) < 0) {
        return INVALID_MUSICAL_NOTE;
    }
    
    //Final key is the addition of the given key input and no. of sharps.
    int finalKey = word_to_num(key) + sharps;
    
    if (finalKey > 11) {
        while (finalKey > 11) {
            finalKey = finalKey - 12;
            finalOctave++;
        }
    }
    //Checking if the note is valid.
    if (finalOctave <= -1 || finalOctave >= 10) {
        return INVALID_MUSICAL_NOTE;
    } else if (finalKey <= -1 || finalKey >= 12) {
        return INVALID_MUSICAL_NOTE;
    }
    struct note *reset = beat->notes;
    struct note *tester = beat->notes;
    
    //Checking if the note to be added matches any of 
    //the existing notes in the beat.
    while (tester != NULL ) {
        if (tester->octave == finalOctave && tester->key == finalKey) {
            return INVALID_MUSICAL_NOTE;
        }
        tester = tester->next;
    }
    
    //Placing the note behind the first note it is lower than.
    
    struct note *add = malloc(sizeof(struct note));
    add->octave = finalOctave;
    add->key = finalKey;
    add->next = NULL;
    
    int switch2 = 0;
    
    struct note *prev = NULL;
    //If there is no note in the beat.
    if (beat->notes == NULL) {
        beat->notes = add;
        return VALID_NOTE;
    } 
    
    //Otherwise if there is a note in the beat.
    else {
        //Looping through the entire linked lists of notes in the beat.
        while (beat->notes != NULL) {
            //If the current existing note has a higher octave
            //than the new note, the new note is inserted ahead of it.
            if (beat->notes->octave > add->octave) {
                struct note *store = beat->notes;           
                beat->notes = add;
                add->next = store;
                return VALID_NOTE;
            }
            //If both notes have the same octave and the current note has a
            //higher key.
            else if (beat->notes->octave == add->octave && beat->notes->key > add->key) {
                //If current note is not the head of the list.
                if (prev != NULL) {
                prev->next = add;
                add->next = beat->notes;
                beat->notes = reset;
                } 
                //If the current note is the head of the list.
                else {
                beat->notes = add;
                add->next = reset;
                }
                return VALID_NOTE;
            } 
            //If both octaves are the same, current note has a lower key 
            //than the new note and the current note happens to be the head 
            else if (beat->notes->octave == add->octave
            && beat->notes->key < add->key 
            && switch2 == 0) {
                add->next = beat->notes->next;
                beat->notes->next = add;
                return VALID_NOTE;
            } 
            //Otherwise if this point has been reached, the above condition can
            //never be met and the current note becomes the note after the
            //current one.
            else {
                prev = beat->notes;
                beat->notes = beat->notes->next;
                switch2 = 1;
            }
        }
        //If none of the notes within the beat are greater than the new note,
        //add the new note to the end.
        if (beat->notes == NULL) {
            beat->notes = reset;
            while (beat->notes->next != NULL) {
                beat->notes = beat->notes->next;
            }
            beat->notes->next = add;
            beat->notes = reset;
        }
    }
    return VALID_NOTE;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Cut a range of beats to the end of a track.
void cut_range_to_end(Track track, int range_length) {
    //If there is no selected beat, do nothing.
    if (track->current == NULL) {
        return;
    }
    //If the range given is less than 1, do nothing.
    if (range_length < 1) {
        return;
    }
    
    
    
    //Make an address to the last beat.
    struct beat *last_beat = track->head;
    while (last_beat->next != NULL) {
        last_beat = last_beat->next;
    }
    
    //Make an address to the beat at the end of the range.
    struct beat *end_of_range = track->current;
    int counter = range_length - 1;
    //Looping until the counter drops to 0.
    while (counter > 0) {
        
        //If the next beat is NULL, exiting the loop.
        if (end_of_range->next == NULL) {
            counter = 0;
        }
        //While the range_length number is not met.
        if (counter != 0) {
            end_of_range = end_of_range->next;
        }
        counter--;
    }
    
    
    
    //If the selected beat is the head.
    if (track->current == track->head) {
        
        //If a beat exists after the beat at the end of the range.
        if (end_of_range->next != NULL) {
            track->head = end_of_range->next;
            last_beat->next = track->current;
            end_of_range->next = NULL;
        }
        return;
    }
    
    //Checking whether the selected beat is the last beat.
    if (track->current == last_beat) {        
        return;
    }
    
    //Creating an address to the beat before the selected beat.
    struct beat *beat_b4_selected = track->head;
    while (beat_b4_selected->next != track->current) {
        beat_b4_selected = beat_b4_selected->next;
    }
    

    //If there is a beat after the range given.
    if (end_of_range->next != NULL) {
        beat_b4_selected->next = end_of_range->next;
        end_of_range->next = NULL;
        last_beat->next = track->current;
    }
    return;
}

// Reverse a list of beats within a range of a track.
int reverse_range(Track track, int range_length) {
    if (track->current == NULL) {
        return 0;
    }
    if (range_length <= 1) {
        return 0;
    }
    
    
    //Creating an address to the beat at the end of the range.
    struct beat *end_of_range = track->current;
    int counter = range_length - 1;
    int range = counter;
    int switch1 = 0;
    while (counter > 0) {
        //Checking if end_of_range is the last beat before the counter finishes.
        if (end_of_range->next == NULL) {
            switch1 = counter;
            counter = 0;
            
        }
        //If end_of_range is at the end, end_of_range = end_of_range->next.
        if (counter != 0) {
            end_of_range = end_of_range->next;
        }
        counter--;
    }
    
    //Checking if the range exceeds the beats left.
    if (switch1 != 0) {
        range = range_length - 1 - switch1;
    }
    
    //Creating an address to the last beat in the list.
    struct beat *last_beat = track->head;
    while (last_beat->next != NULL) {
        last_beat = last_beat->next;
    }
    
     
    struct beat *beat_before_selected = track->head;
    //If selected beat isn't the first beat.
    if (track->current != track->head && track->current != last_beat) {
        while (beat_before_selected->next != track->current) {
            beat_before_selected = beat_before_selected->next;
        }
    } 
    //If the selected beat is the last beat, return 0 beats reversed.
    else if (track->current == last_beat) {
        range = 0;
        return range;
    }
    //If selected beat is neither the first or last beat, beat_before_selected
    //will continue as the track->head.
    
    

    
    
    struct beat *current = track->current;
    //If selected beat isn't the first beat.
    if (beat_before_selected != track->current) {
        //If the range of beats to be reversed is only 2.
        if (range_length == 2) {
            beat_before_selected->next = end_of_range;
            current->next = end_of_range->next;
            end_of_range->next = current;
        } 
        //Else if the range of beats to be reversed is larger than 2.
        else if (range_length > 2) {
            struct beat *prev = end_of_range->next;
            struct beat *next = NULL;
            while (current != end_of_range) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            end_of_range->next = prev;
            beat_before_selected->next = end_of_range;
        }
    } 
    //If the selected beat is the first beat.
    else {
        //If the range of beats to be reversed is only 2.
        if (range_length == 2) {
            current->next = end_of_range->next;
            track->head = end_of_range;
            end_of_range->next = track->current;
        } 
        //Else if the range of beats to be reversed is larger than 2.
        else if (range_length > 2) {
            current = track->current;
            struct beat *prev = end_of_range->next;
            struct beat *next = NULL;
            while (current != end_of_range) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            current->next = prev;
            track->head = end_of_range;                        
        }
    }
    
    return range;
}

int word_to_num(char word) {
    int num = -1;
    if (word == 'A') {
        num = 0;
    } else if (word == 'B') {
        num = 2;
    } else if (word == 'C') {
        num = 3;
    } else if (word == 'D') {
        num = 5;
    } else if (word == 'E') {
        num = 7;
    } else if (word == 'F') {
        num = 8;
    } else if (word == 'G') {
        num = 10;
    }
    
    return num;
}


