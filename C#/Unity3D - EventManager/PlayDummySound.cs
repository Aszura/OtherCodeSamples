using UnityEngine;
using System.Collections;

public class PlayDummySound : MonoBehaviour 
{
	[SerializeField]
	private AudioClip dummyClip;

	private EventManager eventManager;
	
	void Awake () 
	{
		//Get EventManager script and store it in eventManager field.
		GameObject eventManagerObject;

		if ((eventManagerObject = GameObject.FindGameObjectWithTag("EventManager")) == null
		    || (eventManager = eventManagerObject.GetComponent<EventManager>()) == null)
		{
			Debug.LogError(this.name + ": No event manager found!", this);
		}

		StartCoroutine(PlaySomeSound());
	}

	IEnumerator PlaySomeSound () 
	{
		//Wait a second...
		yield return new WaitForSeconds(1.0f);

		//Fire PlaySound event
		eventManager.FireEvent(EventType.PlaySound, this.gameObject, new AudioEventArgs(dummyClip));

		//Start coroutine again
		StartCoroutine(PlaySomeSound());
	}
}
