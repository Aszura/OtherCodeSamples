using UnityEngine;
using System.Collections;
using System.Collections.Generic;

/// <summary>
/// Handles events for the game.
/// </summary>
public class EventManager : MonoBehaviour 
{
    /// <summary>
    /// Struct to store queued events.
    /// </summary>
    struct QueuedEvent
    {
        public GameObject sender;
        public System.EventArgs args;
        public EventType eventType;
    }

    /// <summary>
    /// Delegate for handling events and their callbacks (= template for callback function).
    /// </summary>
    /// <param name="sender">The sender of the event.</param>
    /// <param name="args">The event arguments.</param>
    public delegate void EventHandler(GameObject sender, System.EventArgs args);

    /// <summary>
    /// Dictionary that stores all event listeners.
    /// </summary>
	private Dictionary<EventType, List<EventHandler>> listeners = new Dictionary<EventType, List<EventHandler>>();

    /// <summary>
    /// Stores queued events with the frame as key when it should be fired.
    /// </summary>
    private Dictionary<int, List<QueuedEvent>> queuedEvents = new Dictionary<int, List<QueuedEvent>>();

    /// <summary>
    /// Register a callback for a certain event type.
    /// </summary>
    /// <param name="type">The type the callback is listening to.</param>
    /// <param name="callback">The callback function.</param>
	public void RegisterListener(EventType type, EventHandler callback)
	{
		if(!listeners.ContainsKey(type))
		{
			listeners[type] = new List<EventHandler>();
		}

        if (!listeners[type].Contains(callback))
        {
            listeners[type].Add(callback);
        }
	}

    /// <summary>
    /// Remove a callback for a certain event type.
    /// </summary>
    /// <param name="type">The type the callback is listening to.</param>
    /// <param name="callback">The callback function.</param>
	public void RemoveListener(EventType type, EventHandler callback)
	{
		if(listeners.ContainsKey(type))
		{
			listeners[type].Remove (callback);
		}
		else
		{
			Debug.LogWarning("EventManager: Can't remove callback " + callback + " for event type " + type + " because there are no registered events!", this);
		}
	}

    /// <summary>
    /// Fire the event for the given type and its callbacks.
    /// </summary>
    /// <param name="type">The event type that the callbacks are listening to.</param>
    /// <param name="sender">The sender and caller of the event.</param>
    /// <param name="args">The event arguments.</param>
    public void FireEvent(EventType type, GameObject sender, System.EventArgs args)
	{
		if(listeners.ContainsKey(type))
		{
			foreach(EventHandler listener in listeners[type])
			{
				listener(sender, args);
			}
		}
		else
		{
			Debug.LogWarning("EventManager: Event " + type + " is fired from " + sender + ", but there are no listeners!", this);
		}
	}

    /// <summary>
    /// Queue the event for the given type and its callbacks, so that it is fired next frame.
    /// </summary>
    /// <param name="type">The event type that the callbacks are listening to.</param>
    /// <param name="sender">The sender and caller of the event.</param>
    /// <param name="args">The event arguments.</param>
    /// <param name="framesToWait">The amount of frames the event manager should wait before the event is fired.</param>
    public void QueueEvent(EventType type, GameObject sender, System.EventArgs args, int framesToWait = 1)
    {
        int targetFrame = Time.frameCount + framesToWait;

        if (!queuedEvents.ContainsKey(targetFrame))
        {
            queuedEvents[targetFrame] = new List<QueuedEvent>();
        }

        queuedEvents[targetFrame].Add(new QueuedEvent() { sender = sender, args = args, eventType = type });
    }

    /// <summary>
    /// Update event manager and fire queued events.
    /// </summary>
    void Update()
    {
        if (queuedEvents.ContainsKey(Time.frameCount))
        {
            foreach (QueuedEvent queuedEvent in queuedEvents[Time.frameCount])
            {
                FireEvent(queuedEvent.eventType, queuedEvent.sender, queuedEvent.args);
            }

            queuedEvents.Remove(Time.frameCount);
        }
    }
}
