using UnityEngine;
using System.Collections;

using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Collections.Generic;
using System.Linq;

public class UDPSend : MonoBehaviour
{
    //private static int localport;
    public static Socket unity;

    //prefs
    private string IP;
    public int port;

    //connection stuff
    IPEndPoint remoteEndPoint;
    UdpClient client;

    // Use this for initialization
    void Start()
    {
        Screen.sleepTimeout = SleepTimeout.NeverSleep;
        print("Initiating start sequence");
        init();
    }

    public void init()
    {
        print("UDPSend.init()");

        //IP
        IP = "127.0.0.1"; //193.168.1.2
        port = 993;

        remoteEndPoint = new IPEndPoint(IPAddress.Parse(IP), port);
        client = new UdpClient();

    }

    // Update is called once per frame
    void Update()
    {
        sendCommand();
    }

    private void sendCommand()
    {
        try
        {
            List<byte[]> data = new List<byte[]>();
            addCommand(data);
            byte[] dataf = data
                .SelectMany(a => a)
                .ToArray();
            client.Send(dataf, dataf.Length, remoteEndPoint);
        }
        catch (Exception err)
        {
            print(err.ToString());
        }

    }

    private void addCommand(List<byte[]> b)
    {
        //placeholder values should be replaced with the sims current values
        float magnitudex = 5.0f;
        float magnitudey = 6.0f;
        int direction = 0;
        int orientation = 45;
        b.Add(BitConverter.GetBytes(magnitudex));
        b.Add(BitConverter.GetBytes(magnitudey));
        b.Add(BitConverter.GetBytes(direction));
        b.Add(BitConverter.GetBytes(orientation));
    }

    private void sendString(string message)
    {
        try
        {
            byte[] data = Encoding.UTF8.GetBytes(message);
            client.Send(data, data.Length, remoteEndPoint);
        }
        catch
        {
            print("Error");
        }
    }
}
