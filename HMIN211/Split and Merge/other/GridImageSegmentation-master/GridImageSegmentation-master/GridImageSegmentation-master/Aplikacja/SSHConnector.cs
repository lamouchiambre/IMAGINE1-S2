using Renci.SshNet;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PLGridConnectionApp
{
    class SSHConnector
    {
        public bool Connected { get; set; } = false;

        public string Name { get; set; } = "";
        public string Password { get; set; } = "";
        public string Server { get ; set; } = "";

        SshClient SSHConn;
        ScpClient ScpConn;

        public SSHConnector(string name, string server, string pass)
        {
            Connected = false;

            Name = name;
            Password = pass;
            Server = server;

            SSHConn = new SshClient(server, name, pass);
            ScpConn = new ScpClient(server, name, pass);
        }

        public void NewConnection()
        {
            SSHConn = new SshClient(Server, Name, Password);
            ScpConn = new ScpClient(Server, Name, Password);
        }

        public string StartConnection()
        {
            string answer = "Połączono prawidłowo";
            Connected = false;

            try
            { 
                SSHConn.Connect();
                ScpConn.Connect();

                Connected = true;
            }
            catch (Renci.SshNet.Common.SshOperationTimeoutException e)
            {
                answer = "Błąd polączenia z klastrem: " + e.Message;
            }
            catch (System.Net.Sockets.SocketException e)
            {
                answer = "Błąd polączenia z klastrem: " + e.Message;
            }
            catch (Renci.SshNet.Common.SshConnectionException e)
            {
                answer = "Błąd polączenia z klastrem: " + e.Message;
            }
            catch (Renci.SshNet.Common.SshAuthenticationException e)
            {
                answer = "Błąd autentykacji z klastrem: " + e.Message;
            }

            return answer;
        }

        public void EndConnection()
        {
            SSHConn.Disconnect();
            ScpConn.Disconnect();
        }

        public void SendFile(string localpath, string remotepath)
        {
            FileInfo fi = new FileInfo(localpath);
            ScpConn.Upload(fi, remotepath);
        }

        public void SendFolder(string localpath, string remotepath)
        {
            DirectoryInfo dirInfo = new DirectoryInfo(localpath);
            ScpConn.Upload(dirInfo, remotepath);
        }

        public void GetFile(string localpath, string remotepath)
        {
            FileStream fi = File.Create(localpath);
            ScpConn.Download(remotepath, fi);
        }
        public void GetFolder(string localpath, string remotepath)
        {
            DirectoryInfo dirInfo = new DirectoryInfo(localpath);
            ScpConn.Download(remotepath, dirInfo);
        }


        public void MakeCommand(string command)
        {
            SSHConn.RunCommand(command);
        }
    }
}
