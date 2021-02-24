using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PLGridConnectionApp
{
    class MainOptions
    {
        public string Login { get; set; } = "";
        public string Password { get; set; } = "";

        public int Cluster { get; set; } = 0;

        public int Nods { get; set; } = 0;
        public int Cores { get; set; } = 0;
        public int Ram { get; set; } = 0;

        public string GrantID { get; set; } = "";
        public int MaxTime { get; set; } = 0;

        public string[] ServAdresses = new string[4];
        public string[] ServNames = new string[4];

        public MainOptions(string log, string pass, int clus, int n, int c, int r, string id, int time)
        {
            Login = log;
            Password = pass;

            Cluster = clus;

            Nods = n;
            Cores = c;
            Ram = r;

            GrantID = id;
            MaxTime = time;

            ServNames[0] = "";
            ServNames[1] = "Kraków CYFRONET Zeus";
            ServNames[2] = "Wrocław WCSS Bem";
            ServNames[3] = "Poznań PCSS Inula";

            ServAdresses[0] = "";
            ServAdresses[1] = "zeus.cyfronet.pl";
            ServAdresses[2] = "ui.plgrid.wcss.wroc.pl";
            ServAdresses[3] = "client.qcg.psnc.pl";
        }
    }
}
