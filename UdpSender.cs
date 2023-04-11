using System.Net;
using System.Net.Sockets;
using System.Text;
using UnityEngine;

public class UdpSender : MonoBehaviour
{
    public string targetIpAddress = "ここにESP32のIPアドレスを入力"; 
    //ESP32に書き込んだときシリアルモニタに表示されるESP32のIPアドレスを入力
    
    public int targetPort = 3333;

    private UdpClient udpClient;

    void Start()
    {
        udpClient = new UdpClient();
    }

    public void SendLedOn()
    {
        Send("LED_ON");
    }

    public void SendLedOff()
    {
        Send("LED_OFF");
    }

    private void Send(string message)
    {
        try
        {
            byte[] data = Encoding.UTF8.GetBytes(message);
            udpClient.Send(data, data.Length, targetIpAddress, targetPort);
        }
        catch (SocketException e)
        {
            Debug.LogError($"SocketException: {e}");
        }
    }

    private void OnDestroy()
    {
        udpClient.Close();
    }
}
