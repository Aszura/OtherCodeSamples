using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class AudioSystem : MonoBehaviour 
{
    private EventManager eventManager;
    private List<AudioSource> audioSourceList = new List<AudioSource>();

	private void Start () 
    {
        //Get event manager and register listeners.
        GameObject eventManagerObject;

        if ((eventManagerObject = GameObject.FindGameObjectWithTag("EventManager")) == null
            || (eventManager = eventManagerObject.GetComponent<EventManager>()) == null)
        {
            Debug.LogError(this.name + ": No event manager found!", this);
        }

        eventManager.RegisterListener(EventType.PlaySound, OnPlaySound);

	}

    private void OnPlaySound(GameObject sender, System.EventArgs eventArgs)
    {
        AudioEventArgs audioArgs;

        if ((audioArgs = (AudioEventArgs)eventArgs) != null)
        {
            AudioSource audioSrc = gameObject.AddComponent<AudioSource>();
            audioSrc.clip = audioArgs.Clip;
            audioSrc.Play();
            audioSourceList.Add(audioSrc);
            StartCoroutine(StopSound(audioSrc));
        }
        else
        {
            Debug.LogError(this.name + ": Wrong event arg type!", this);
        }
    }

    private IEnumerator StopSound(AudioSource audioSource)
    {
        do
        {
            yield return null;
        } while (audioSource.isPlaying);

        audioSourceList.Remove(audioSource);
        Destroy(audioSource);
    }
}
