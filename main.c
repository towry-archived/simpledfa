
#include <stdio.h>

// https://zh.wikipedia.org/wiki/%E7%A1%AE%E5%AE%9A%E6%9C%89%E9%99%90%E7%8A%B6%E6%80%81%E8%87%AA%E5%8A%A8%E6%9C%BA

typedef struct transition_s {
	int state;
	char input;
	int next_state;
} transition_t;


int 
find_next_state(transition_t *ts, int ts_len, int state, char input) 
{
	transition_t *transition;

	for (int i = 0; i < ts_len; i++) {
		transition = &ts[i];

		if (transition->state == state && transition->input == input) {
			return transition->next_state;
		}
	}

	return -1;
}


int
main()
{
	// The input string.
	const char *sequence = "100101001101010100111";
	int sequence_len = 21;

	// States of the DFA.
	int states[2] = {1, 2};
	// Final states of the DFA.
	int final_states[1] = {1};
	int final_states_len = 1;

	// Accept characters of the DFA.
	char sigma[2] = {'0', '1'};
	// Start state.
	int s = 1;

	// Variables.
	char current_input;
	int current_state = s;

	// Transition.
	transition_t transitions[4];
	transitions[0].state = 1;
	transitions[0].input = '0';
	transitions[0].next_state = 2;

	transitions[1].state = 1;
	transitions[1].input = '1';
	transitions[1].next_state = 1;

	transitions[2].state = 2;
	transitions[2].input = '0';
	transitions[2].next_state = 1;

	transitions[3].state = 2;
	transitions[3].input = '1';
	transitions[3].next_state = 2;

	for (int i = 0; i < sequence_len; i++) {
		current_input = sequence[i];
		current_state = find_next_state(transitions, 4, current_state, current_input);
		if (current_state == -1) {
			// Wrong character.
			fprintf(stderr, "wrong character.\n");
			return 1;
		}
	}

	// Check if the final state is in the accepting states.
	for (int i = 0; i < final_states_len; i++) {
		if (final_states[i] == current_state) {
			printf("Accepted! state: %d\n", current_state);
			return 0;
		}
	}

	printf("Not accepted at state: %d.\n", current_state);
	return 0;
}
