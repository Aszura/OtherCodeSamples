using UnityEngine;
using System.Collections;
using System.Collections.Generic;

/// <summary>
/// General FSM with delegates.
/// </summary>
public class FiniteStateMachine
{
    /// <summary>
    /// Transition for changing states.
    /// </summary>
    public class Transition
    {
        /// <summary>
        /// Handler that checks if the transition should happen.
        /// </summary>
        public StateTrigger Trigger { get; set; }

        /// <summary>
        /// State to change to.
        /// </summary>
        public State NextState { get; set; }

        /// <summary>
        /// Handler for action when changing state.
        /// </summary>
        public StateAction ChangeAction { get; set; }
    }

    /// <summary>
    /// An object's state.
    /// </summary>
    public class State
    {
        /// <summary>
        /// The transitions for this state.
        /// </summary>
        private List<Transition> transitions = new List<Transition>();

        /// <summary>
        /// Handler that is called when updating.
        /// </summary>
        public StateAction Action { get; set; }

        /// <summary>
        /// Add transition to state.
        /// </summary>
        /// <param name="transition"></param>
        public void AddTransition(Transition transition)
        {
            transitions.Add(transition);
        }

        /// <summary>
        /// Change for next update cycle.
        /// </summary>
        /// <returns>Next state.</returns>
        public State GetNextState()
        {
            foreach (Transition transition in transitions)
            {
                if (transition.Trigger())
                {
                    if (transition.ChangeAction != null)
                    {
                        transition.ChangeAction();
                    }
                    return transition.NextState;
                }
            }

            return this;
        }
    }

    /// <summary>
    /// Delegate for triggers to fire transitions.
    /// </summary>
    /// <returns></returns>
    public delegate bool StateTrigger();

    /// <summary>
    /// Delegate for actions in the FSM.
    /// </summary>
    public delegate void StateAction();

    /// <summary>
    /// The state the FSM is currently in.
    /// </summary>
    private State currentState;

    /// <summary>
    /// Constructor. Sets first state.
    /// </summary>
    /// <param name="startState">First state.</param>
    public FiniteStateMachine(State startState)
    {
        currentState = startState;
    }
	
    /// <summary>
    /// Update FSM and check for a new state.
    /// </summary>
	public void Update () 
    {
        currentState.Action();
        currentState = currentState.GetNextState();
	}
}
