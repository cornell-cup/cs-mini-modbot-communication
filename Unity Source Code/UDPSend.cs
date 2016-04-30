using UnityEngine;
using System.Collections;

using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Collections.Generic;

public class Command {
    double dosomething;

}
public class UDPSend : MonoBehaviour {
    //private static int localport;
    public static Socket unity;

    //prefs
    private string IP;
    public int port;

    //connection stuff
    IPEndPoint remoteEndPoint;
    UdpClient client;

    //response boolean
    public bool response = false;

    //send boolean
    public bool sent = false;

	// Use this for initialization
	void Start () {
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

        remoteEndPoint = new IPEndPoint(IPAddress.Parse(IP),port);
        client = new UdpClient();

    }

    // Update is called once per frame
    void Update () {
        Command newCommand = GetCurrCommand();
        sendCommand(b);
	}

    private void sendCommand(Command b)
    {
        try 
        {
            List<byte> data = new List<byte>();
            addCommand1(data, b);
            addCommand2(data, b);
            //...
            byte[] dataf = data.ToArray();
            client.send(dataf, dataf.Length, remoteEndPoint);
        } 
        catch (Exception err) 
        {
            print(err.toString());
        }

    }
    private void GetCurrCommand() {
        //neeed to grab current command from simulation.
    }
    private void addCommand1(List<byte> b, Command p)
    {
        int velocity = p.velocity;
        b.add(Encoding.UTF8.GetBytes(velocity));

    }
    private void addCommand2(List<byte> b, Command p)
    {
        double direction = p.direction;
        b.add(Encoding.UTF8.GetBytes(direction));
    }

    private void sendString(string message) {
       try
        {
            byte[] data = Encoding.UTF8.GetBytes(message);
            client.Send(data, data.Length, remoteEndPoint);
        } catch
        {
            print("Error");
        }
    }
}
