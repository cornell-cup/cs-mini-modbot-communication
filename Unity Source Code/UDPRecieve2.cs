using UnityEngine;
using System.Collections;

using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;

public struct RecieveBlob 
{
	public int id;
	public double time;
	public double x;
	public double y;
	public int innerColor;
	public int outerColor;
	public double orientation;
	public double velocityRot;
	public double veloictyx;
	public double veloictyy;
}
public class ComandReceive : MonoBehavior
{
	Thread receiveThread;
	public int port;

	public void Start() {
		receieveThread = new Thread(
			new ThreadStart(ReceiveData);
		)
		receiveThread.IsBackground = true;
		receiveThread.Start();
	}
	private void ReceiveData() {
		client = new UdpClient(port);
		byte[] data = new byte[68];
		IPEndPoint unityEp = new IPEndPoint(IPAddress.Any,0);
		client.Client.Bind(unityEp);
		while(1) {
			try {
				print("Listening");
				data = client.Receive(ref unityEp);
				string text = Encoding.UTF8.GetString(data);
			}
			catch (Exception err) {
				print(err.ToString());
			}
		}
		RecieveBlob p = decodePacket(data);
	}
	private void decodePacket(byte[] p) {
		RecieveBlob r = new RecieveBlob(
           BitConverter.ToInt32(p, 0),
           BitConverter.ToDouble(p, 4),
           BitConverter.ToDouble(p, 12),
           BitConverter.ToDouble(p, 20),
           BitConverter.ToInt32(p, 28),
           BitConverter.ToInt32(p, 32),
           BitConverter.ToDouble(p, 36),
           BitConverter.ToDouble(p, 44),
           BitConverter.ToDouble(p, 52),
           BitConverter.ToDouble(p, 60)
	    );
	    return r;
	}

}
