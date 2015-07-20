using UnityEngine;
using System.Collections;

public class AudioEventArgs : System.EventArgs
{
    public AudioClip Clip { get; set; }

    public AudioEventArgs(AudioClip clip)
    {
        Clip = clip;
    }
}