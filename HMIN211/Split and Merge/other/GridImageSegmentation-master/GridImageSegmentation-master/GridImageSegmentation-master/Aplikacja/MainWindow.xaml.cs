using Microsoft.WindowsAPICodePack.Dialogs;
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;
using System.Drawing;

namespace PLGridConnectionApp
{
    /// <summary>
    /// Logika interakcji dla klasy MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        List<string> imagesList = new List<string>();
        int tempImg = 0;

        int selectedMeth = -1;

        string saveFolderPath;

        Canvas[] SegmCanvas = new Canvas[5];
        MenuItem[] SegmItems = new MenuItem[5];

        MainOptions mainOpts;
        SegmentOptions segmOpts;
        SSHConnector plgConn;

        TextBox Avg = new TextBox();
        TextBox Var = new TextBox();

        Slider LinesWidth = new Slider();
        Slider LinesHeight = new Slider();
        Slider RoundWidth = new Slider();
        Slider RoundHeight = new Slider();


        public MainWindow()
        {
            InitializeComponent();

            SegmCanvas[0] = SplitAndMergeOpts;
            SegmCanvas[1] = WaterSplitOpts;
            SegmCanvas[2] = LinesOpts;
            SegmCanvas[3] = RoundOpts;
            SegmCanvas[4] = FiguresOpts;

            SegmItems[0] = SplitAndMergeMenuItem;
            SegmItems[1] = WaterSplitMenuItem;
            SegmItems[2] = LinesMenuItem;
            SegmItems[3] = RoundMenuItem;
            SegmItems[4] = FiguresMenuItem;

            Avg = AverageTextBox;
            Var = VariantTextBox;

            LinesWidth = LinesWidthSlider;
            LinesHeight = LinesHeightSlider;
            RoundWidth = RoundWidthSlider;
            RoundHeight = RoundHeightSlider;

            string directory = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            StreamReader optsFile = new StreamReader(directory + "/opts.txt");

            mainOpts = new MainOptions(optsFile.ReadLine(), optsFile.ReadLine(), int.Parse(optsFile.ReadLine()), int.Parse(optsFile.ReadLine()), int.Parse(optsFile.ReadLine()), int.Parse(optsFile.ReadLine()), optsFile.ReadLine(), int.Parse(optsFile.ReadLine()));
            segmOpts = new SegmentOptions(16, 100, 10, 3, 3, 10, 10, 2, 40, "");

            optsFile.Close();
            plgConn = new SSHConnector(mainOpts.Login, mainOpts.ServAdresses[mainOpts.Cluster], mainOpts.Password);
        }

        private void NewImageMenuItem_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog openImg = new Microsoft.Win32.OpenFileDialog();
            openImg.FileName = "Obraz"; 
            openImg.DefaultExt = ".bmp";
            openImg.Filter = "(.bmp)|*.bmp|(.jpg)|*.jpg|(.png)|*.png";

            Nullable<bool> result = openImg.ShowDialog();

            if (result == true)
            {
                ImageTextBox.Text = "Obraz: " + openImg.FileName;

                FileInfo info = new FileInfo(openImg.FileName);
                ImageInfoName_TextBlock.Text = info.Name;
                ImageInfoDirectory_TextBlock.Text = info.DirectoryName;
                Bitmap img = new Bitmap(openImg.FileName);
                ImageInfoSize_TextBlock.Text = img.Width + " x " + img.Height + " px";

                Uri imageUri = new Uri(openImg.FileName);
                Image.Source = new BitmapImage(imageUri);

                imagesList.Clear();

                foreach (string image in openImg.FileNames)
                {
                    imagesList.Add(image);
                }

                if (imagesList.Count > 1)
                {
                    PrevImgButton.IsEnabled = true;
                    NextImgButton.IsEnabled = true;
                }
                else
                {
                    PrevImgButton.IsEnabled = false;
                    NextImgButton.IsEnabled = false;
                }

                checkButtonUnlock();
            }
        }

        private void PrevImgButton_Click(object sender, RoutedEventArgs e)
        {
            --tempImg;

            if (tempImg < 0)
            {
                tempImg = imagesList.Count - 1;
            }

            ImageTextBox.Text = "Obraz: " + imagesList[tempImg];

            FileInfo info = new FileInfo(imagesList[tempImg]);
            ImageInfoName_TextBlock.Text = info.Name;
            Bitmap img = new Bitmap(imagesList[tempImg]);
            ImageInfoSize_TextBlock.Text = img.Width + " x " + img.Height + " px";


            Uri imageUri = new Uri(imagesList[tempImg]);
            Image.Source = new BitmapImage(imageUri);
        }

        private void NextImgButton_Click(object sender, RoutedEventArgs e)
        {
            ++tempImg;

            if (tempImg >= imagesList.Count)
            {
                tempImg = 0;
            }

            ImageTextBox.Text = "Obraz: " + imagesList[tempImg];

            FileInfo info = new FileInfo(imagesList[tempImg]);
            ImageInfoName_TextBlock.Text = info.Name;
            Bitmap img = new Bitmap(imagesList[tempImg]);
            ImageInfoSize_TextBlock.Text = img.Width + " x " + img.Height + " px";

            Uri imageUri = new Uri(imagesList[tempImg]);
            Image.Source = new BitmapImage(imageUri);
        }

        //////////////////////////////////Menu główne - funkcje kontrolek/////////////////////////////

        private void NewFolderMenuItem_Click(object sender, RoutedEventArgs e)
        {

            CommonOpenFileDialog openFolder = new CommonOpenFileDialog();
            openFolder.IsFolderPicker = true;

            if (openFolder.ShowDialog() == CommonFileDialogResult.Ok)
            {
                DirectoryInfo dirInfo = new DirectoryInfo(openFolder.FileName);
                FileInfo[] info = dirInfo.GetFiles("*.bmp");
                bool notCleared = true;

                if (info.Length > 0 && notCleared)
                {
                    imagesList.Clear();
                    notCleared = false;
                }

                foreach (FileInfo f in info)
                {
                    imagesList.Add(f.FullName);
                }

                info = dirInfo.GetFiles("*.jpg");

                if (info.Length > 0 && notCleared)
                {
                    imagesList.Clear();
                    notCleared = false;
                }

                foreach (FileInfo f in info)
                {
                    imagesList.Add(f.FullName);
                }

                info = dirInfo.GetFiles("*.png");

                if (info.Length > 0 && notCleared)
                {
                    imagesList.Clear();
                }

                foreach (FileInfo f in info)
                {
                    imagesList.Add(f.FullName);
                }
            }

            if (imagesList.Count > 0)
            {
                ImageTextBox.Text = "Obraz: " + imagesList[0];

                FileInfo info = new FileInfo(imagesList[0]);
                ImageInfoName_TextBlock.Text = info.Name;
                ImageInfoDirectory_TextBlock.Text = info.DirectoryName;
                Bitmap img = new Bitmap(imagesList[0]);
                ImageInfoSize_TextBlock.Text = img.Width + " x " + img.Height + " px";

                Uri imageUri = new Uri(imagesList[0]);
                Image.Source = new BitmapImage(imageUri);

                if (imagesList.Count > 1)
                {
                    PrevImgButton.IsEnabled = true;
                    NextImgButton.IsEnabled = true;
                }
                else
                {
                    PrevImgButton.IsEnabled = false;
                    NextImgButton.IsEnabled = false;
                }
            }

            checkButtonUnlock();
        }

        private void SaveFolderMenuItem_Click(object sender, RoutedEventArgs e)
        {
            CommonOpenFileDialog saveFolder = new CommonOpenFileDialog();
            saveFolder.IsFolderPicker = true;

            if (saveFolder.ShowDialog() == CommonFileDialogResult.Ok)
            {
                saveFolderPath = saveFolder.FileName;

                FolderTextBox.Text = "Folder zapisu: " + saveFolder.FileName;
            }

            checkButtonUnlock();
        }

        private void ExitMenuItem_Click(object sender, RoutedEventArgs e)
        {

        }

        private void SplitAndMergeMenuItem_Click(object sender, RoutedEventArgs e)
        {
            foreach (Canvas segm in SegmCanvas)
            {
                segm.Visibility = Visibility.Hidden;
            }

            foreach (MenuItem segm in SegmItems)
            {
                segm.IsChecked = false;
            }

            MinSizeTextBox.Text = segmOpts.SMMinSize.ToString();
            AverageTextBox.Text = segmOpts.SMAverage.ToString();
            VariantTextBox.Text = segmOpts.SMVariant.ToString();

            SplitAndMergeOpts.Visibility = Visibility.Visible;
            SplitAndMergeMenuItem.IsChecked = true;
            selectedMeth = 0;

            checkButtonUnlock();
        }

        private void WaterSplitMenuItem_Click(object sender, RoutedEventArgs e)
        {
            foreach (Canvas segm in SegmCanvas)
            {
                segm.Visibility = Visibility.Hidden;
            }

            foreach (MenuItem segm in SegmItems)
            {
                segm.IsChecked = false;
            }

            WaterSplitOpts.Visibility = Visibility.Visible;
            WaterSplitMenuItem.IsChecked = true;
            selectedMeth = 1;

            checkButtonUnlock();
        }

        private void LinesMenuItem_Click(object sender, RoutedEventArgs e)
        {
            foreach (Canvas segm in SegmCanvas)
            {
                segm.Visibility = Visibility.Hidden;
            }

            foreach (MenuItem segm in SegmItems)
            {
                segm.IsChecked = false;
            }

            LinesWidthSlider.Value = segmOpts.LinesWidth;
            LinesHeightSlider.Value = segmOpts.LinesHeight;

            LinesOpts.Visibility = Visibility.Visible;
            LinesMenuItem.IsChecked = true;
            selectedMeth = 2;

            checkButtonUnlock();
        }

        private void RoundMenuItem_Click(object sender, RoutedEventArgs e)
        {
            foreach (Canvas segm in SegmCanvas)
            {
                segm.Visibility = Visibility.Hidden;
            }

            foreach (MenuItem segm in SegmItems)
            {
                segm.IsChecked = false;
            }

            RoundWidthSlider.Value = segmOpts.RoundWidth;
            RoundHeightSlider.Value = segmOpts.RoundHeight;

            RoundXTextBox.Text = segmOpts.RoundX.ToString();
            RoundYTextBox.Text = segmOpts.RoundY.ToString();
            RoundRTextBox.Text = segmOpts.RoundR.ToString();
            RoundTrshTextBox.Text = segmOpts.RoundTrshld.ToString();

            RoundOpts.Visibility = Visibility.Visible;
            RoundMenuItem.IsChecked = true;
            selectedMeth = 3;

            checkButtonUnlock();
        }

        private void FiguresMenuItem_Click(object sender, RoutedEventArgs e)
        {
            foreach (Canvas segm in SegmCanvas)
            {
                segm.Visibility = Visibility.Hidden;
            }

            foreach (MenuItem segm in SegmItems)
            {
                segm.IsChecked = false;
            }

            FiguresSplitWidthSlider.Value = segmOpts.FiguresWidth;
            FiguresSplitHeightSlider.Value = segmOpts.FiguresHeight;

            FiguresOpts.Visibility = Visibility.Visible;
            FiguresMenuItem.IsChecked = true;
            selectedMeth = 4;

            checkButtonUnlock();
        }

        private void ConnectCNETMenuItem_Click(object sender, RoutedEventArgs e)
        {
            ConnectCNETMenuItem.IsChecked = true;
            ConnectWCSSMenuItem.IsChecked = false;
            ConnectPCSSMenuItem.IsChecked = false;

            mainOpts.Cluster = 1;

            plgConn.Server = mainOpts.ServAdresses[mainOpts.Cluster];

            InfoTextBox.Text = "Wybrano klaster: Zeus (Kraków)";
        }

        private void ConnectWCSSMenuItem_Click(object sender, RoutedEventArgs e)
        {
            ConnectCNETMenuItem.IsChecked = false;
            ConnectWCSSMenuItem.IsChecked = true;
            ConnectPCSSMenuItem.IsChecked = false;

            mainOpts.Cluster = 2;

            plgConn.Server = mainOpts.ServAdresses[mainOpts.Cluster];

            InfoTextBox.Text = "Wybrano klaster: Bem (Wrocław)";
        }

        private void ConnectPCSSMenuItem_Click(object sender, RoutedEventArgs e)
        {
            ConnectCNETMenuItem.IsChecked = false;
            ConnectWCSSMenuItem.IsChecked = false;
            ConnectPCSSMenuItem.IsChecked = true;

            mainOpts.Cluster = 3;

            plgConn.Server = mainOpts.ServAdresses[mainOpts.Cluster];

            InfoTextBox.Text = "Wybrano klaster: Inula (Poznań)";
        }

        //////////////////////////////////Dane identyfikacyjne - funkcje kontrolek//////////////////////////////////

        private void LoginMenuItem_Click(object sender, RoutedEventArgs e)
        {
            LoginTextBox.Text = mainOpts.Login;
            PassPasswordBox.Password = mainOpts.Password;

            LoginOpts.Visibility = Visibility.Visible;
        }

        private void LoginCancelButton_Click(object sender, RoutedEventArgs e)
        {
            LoginOpts.Visibility = Visibility.Hidden;
            InfoTextBox.Text = "Anulowano zapis danych identyfikacyjnych";
        }

        private void LoginSaveButton_Click(object sender, RoutedEventArgs e)
        {
            mainOpts.Login = LoginTextBox.Text;
            mainOpts.Password = PassPasswordBox.Password;
            LoginOpts.Visibility = Visibility.Hidden;

            plgConn.Name = mainOpts.Login;
            plgConn.Password = mainOpts.Password;

            InfoTextBox.Text = "Zapisano dane identyfikacyjne";
        }

        //////////////////////////////////Zasoby - funkcje kontrolek//////////////////////////////////

        private void QueueMenuItem_Click(object sender, RoutedEventArgs e)
        {
            QueueNodsSlider.Value = mainOpts.Nods;
            QueueCoresSlider.Value = mainOpts.Cores;
            QueueRAMSlider.Value = mainOpts.Ram;

            QueueGrantTextBox.Text = mainOpts.GrantID;

            //QueueMaxTimeTextBox.Text = mainOpts.MaxTime;

            QueueOpts.Visibility = Visibility.Visible;
        }

        private void QueueCancelButton_Click(object sender, RoutedEventArgs e)
        {
            QueueOpts.Visibility = Visibility.Hidden;
            InfoTextBox.Text = "Anulowano zapis ustawień używanych zasobów";
        }

        private void QueueSaveButton_Click(object sender, RoutedEventArgs e)
        {
            mainOpts.Nods = (int)QueueNodsSlider.Value;
            mainOpts.Cores = (int)QueueCoresSlider.Value;
            mainOpts.Ram = (int)QueueRAMSlider.Value;

            mainOpts.GrantID = QueueGrantTextBox.Text;

            QueueOpts.Visibility = Visibility.Hidden;
            InfoTextBox.Text = "Zapisano ustawienia używanych zasobów";
        }

        //////////////////////////////////Opcje Podziału i Łączenia - kontrolki//////////////////////////////////

        private void MinSizeTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            //saveControlls();
        }

        private void AverageTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            //saveControlls();
        }

        private void VariantTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            //saveControlls();
        }

        private void AverageRadioButton_Checked(object sender, RoutedEventArgs e)
        {
            Avg.IsEnabled = true;
            Var.IsEnabled = false;
        }

        private void VariantRadioButton_Checked(object sender, RoutedEventArgs e)
        {
            AverageTextBox.IsEnabled = false;
            VariantTextBox.IsEnabled = true;
        }


        //////////////////////////////////Opcje Segmentacji Wododziałowej - kontrolki//////////////////////////////////

        //////////////////////////////////Opcje Hougha Linie - kontrolki//////////////////////////////////

        private void LinesWidthSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            //saveControlls();
        }

        private void LinesHeightSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            //saveControlls();
        }

        //////////////////////////////////Opcje Hougha Okręgi - kontrolki//////////////////////////////////

        private void RoundWidthSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            //saveControlls();
        }

        private void RoundHeightSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            //saveControlls();
        }

        private void RoundXTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            //saveControlls();
        }

        private void RoundYTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            //saveControlls();
        }

        private void RoundRTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            // saveControlls();
        }

        private void RoundTrshTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            //saveControlls();
        }

        private void StartButton_Click(object sender, RoutedEventArgs e)
        {
            SaveControlls();
            Console.WriteLine(imagesList.Count);
            string info = plgConn.StartConnection();
            //plgConn.MakeCommand("touch ttesty.a");

            if (plgConn.Connected == false)
            {
                InfoTextBox.Text = info;
                ConnStateTextBlock.Text = "Nie połączono";

                Uri imageUri = new Uri("ic_disconn.png");
                ConnectIcon_Image.Source = new BitmapImage(new Uri("/ic_disconn.png", UriKind.Relative));

                checkButtonUnlock();
            }
            else
            {
                string[] imagenames = new string[imagesList.Count];
                int itr = 0;

                Directory.CreateDirectory(saveFolderPath + "\\txtfiles\\");
                foreach (string image in imagesList)
                {
                    //Uri imageUri = new Uri(image);
                    Bitmap img = new Bitmap(image);
                    string[] arr = image.Split('\\');
                    string tmp = arr[arr.Length - 1];
                    int find = tmp.IndexOf('.');

                    string filename = tmp.Substring(0, find) + ".txt";
                    string filepath = saveFolderPath + "\\txtfiles\\" + tmp.Substring(0, find) + ".txt";

                    StreamWriter txt = File.CreateText(filepath);

                    txt.WriteLine(img.Width + " " + img.Height);


                    for (int y = 0; y < img.Height; ++y)
                    {
                        for (int x = 0; x < img.Width; ++x)
                        {
                            txt.Write(img.GetPixel(x, y).R + " ");
                        }

                        txt.WriteLine("");
                    }

                    txt.Close();

                    Console.WriteLine(filepath);
                    Console.WriteLine(filename);

                    imagenames[itr] = tmp.Substring(0, find);

                    plgConn.MakeCommand("mkdir " + imagenames[itr]);

                    plgConn.SendFile(filepath, filename);

                    File.Delete(filepath);


                    if (selectedMeth == 0)
                    {
                        int farg = segmOpts.SMMinSize;
                        int sarg = segmOpts.SMVariant;

                        plgConn.MakeCommand("./SplitAndMerge.out " + farg + " " + sarg + " " + filename);
                    }
                    else if (selectedMeth == 1)
                    {
                        plgConn.MakeCommand("./WaterSplit.out 10 15 " + filename);
                    }
                    else if (selectedMeth == 2)
                    {
                        int farg = segmOpts.LinesWidth;
                        int sarg = segmOpts.LinesHeight;

                        plgConn.MakeCommand("./HoughTransform.out " + farg + " " + sarg + " " + filename);
                    }
                    else if (selectedMeth == 3)
                    {
                        int farg = segmOpts.RoundWidth;
                        int sarg = segmOpts.RoundHeight;

                        plgConn.MakeCommand("./HoughRound.out " + farg + " " + sarg + " " + filename);
                    }
                    else
                    {
                        plgConn.MakeCommand("./HoughPattern.out " + filename);
                    }

                    Directory.CreateDirectory(saveFolderPath + "\\" + imagenames[itr] + "\\");
                    plgConn.GetFolder(saveFolderPath + "\\" + imagenames[itr] + "\\", imagenames[itr]);

                    plgConn.MakeCommand("rm " + imagenames[itr] + ".txt");
                    plgConn.MakeCommand("rm -r " + imagenames[itr]);

                    foreach (string file in Directory.GetFiles(saveFolderPath + "\\" + imagenames[itr] + "\\"))
                    {
                        if (file.Contains(".txt"))
                        {
                            Console.WriteLine(file);
                            StreamReader tmptxt = new StreamReader(file);

                            int imgW = 0;
                            int imgH = 0;
                            int pos = 0;
                            int ch = 0;
                            Bitmap mapka = null;

                            String line = tmptxt.ReadLine();

                            pos = line.IndexOf(" ");
                            imgW = int.Parse(line.Substring(0, pos));
                            imgH = int.Parse(line.Substring(pos + 1));

                            mapka = new Bitmap(imgW, imgH);


                            for (int y = ch; y < imgH; ++y)
                            {
                                int check = y;
                                line = tmptxt.ReadLine();
                                line = line.TrimStart();
                                for (int x = 0; x < imgW; ++x)
                                {
                                    pos = line.IndexOf(" ");
                                    if (pos >= 0)
                                    {
                                        string nl = line.Substring(0, pos);

                                        if (nl != "")
                                        {
                                            int px = int.Parse(nl);
                                            mapka.SetPixel(x, y, Color.FromArgb(px, px, px));
                                        }

                                        line = line.Substring(pos + 1);
                                    }
                                }
                            }


                            tmptxt.Close();
                            int fnd = file.LastIndexOf("\\");
                            string newname = file.Substring(fnd + 1);
                            fnd = newname.IndexOf(".");

                            mapka.Save(saveFolderPath + "\\" + imagenames[itr] + "\\" + newname.Substring(0, fnd) + ".bmp");
                            File.Delete(file);
                        }
                    }


                    ++itr;
                }

                //plgConn.StartConnection();
                //plgConn.SendFolder(saveFolderPath + "\\txtfiles\\", "\\testfolder\\");




                //plgConn.GetFolder(saveFolderPath, "Trash");
                Directory.Delete(saveFolderPath + "\\txtfiles\\");
                plgConn.EndConnection();
            }
        }

        private void AboutMenuItem_Click(object sender, RoutedEventArgs e)
        {
            SaveControlls();
        }

        private void SaveControlls()
        {
            ///Console.WriteLine(segmOpts.SMMinSize);

            if (selectedMeth == 0)
            {
                segmOpts.SMMinSize = int.Parse(MinSizeTextBox.Text.Trim());
                segmOpts.SMAverage = int.Parse(AverageTextBox.Text.Trim());
                segmOpts.SMVariant = int.Parse(VariantTextBox.Text.Trim());

                Console.WriteLine(segmOpts.SMMinSize);
                Console.WriteLine(segmOpts.SMVariant);
            }
            else if (selectedMeth == 1)
            {

            }
            else if (selectedMeth == 2)
            {
                segmOpts.LinesWidth = (int)LinesWidthSlider.Value;
                segmOpts.LinesHeight = (int)LinesHeightSlider.Value;

                Console.WriteLine(segmOpts.LinesWidth);
                Console.WriteLine(segmOpts.LinesHeight);
            }
            else if (selectedMeth == 3)
            {
                segmOpts.RoundWidth = (int)RoundWidthSlider.Value;
                segmOpts.RoundHeight = (int)RoundHeightSlider.Value;
                segmOpts.RoundX = int.Parse(RoundXTextBox.Text);
                segmOpts.RoundY = int.Parse(RoundYTextBox.Text);
                segmOpts.RoundR = int.Parse(RoundRTextBox.Text);
                segmOpts.RoundTrshld = int.Parse(RoundTrshTextBox.Text);
            }
            else
            {

            }
        }

        private void TestConnMenuItem_Click(object sender, RoutedEventArgs e)
        {
            plgConn.NewConnection();
            string answer = plgConn.StartConnection();

            //plgConn.GetFile("test.txt", "test.a");

            InfoTextBox.Text = answer;

            Console.WriteLine(plgConn.Server);

            if (plgConn.Connected)
            {
                ConnStateTextBlock.Text = "Połączono: " + mainOpts.ServNames[mainOpts.Cluster];
                //plgConn.MakeCommand("touch test.a");

                Uri imageUri = new Uri("ic_conn.png", UriKind.Relative);
                ConnectIcon_Image.Source = new BitmapImage(new Uri("ic_conn.png", UriKind.Relative));
                checkButtonUnlock();
            }
            else
            {
                ConnStateTextBlock.Text = "Nie połączono";

                Uri imageUri = new Uri("ic_disconn.png", UriKind.Relative);

                ConnectIcon_Image.Source = new BitmapImage(new Uri("ic_disconn.png", UriKind.Relative));
            }

            plgConn.EndConnection();
        }

        private void checkButtonUnlock()
        {
            if(ImageTextBox.Text != "Wybierz obraz lub folder obrazów..." && FolderTextBox.Text != "Wybierz folder zapisu..." && selectedMeth != -1 && plgConn.Connected == true)
            {
                StartButton.IsEnabled = true;
            }
            else
            {
                StartButton.IsEnabled = false;
            }
        }
    }
}
