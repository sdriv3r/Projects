using System;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using Newtonsoft.Json;
using System.Collections.Generic;
using Rona;

namespace PriceMe
{
    class Program
    {

        struct Item
        {
            public string Store;
            public string Name;
            public string Model;
            public string SKU;

            public Item (string ItemStore, string ItemName, string ItemModel, string ItemSKU)
            {
                Store = ItemStore;
                Name = ItemName;
                Model = ItemModel;
                SKU = ItemSKU;
            }
        }

        static void Main(string[] args)
        {
            Item item = new Item(args[0], "", "", args[1]);
            Console.WriteLine("Item is from: " + item.Store);
            Console.WriteLine("Item SKU entered: " + item.SKU);

            float price = float.MaxValue;
            Task<float> task;

                switch (item.Store.ToLower().Split(new char[] { '_' })[0])
            {
                case "rona":

                    if (item.Store.ToLower() == "rona")
                    {
                        string Cheapest_Store = string.Empty;
                        foreach (KeyValuePair<string, RonaStore> entry in Rona.Rona.Stores)
                        {
                            item.Store = "rona_" + entry.Key;
                            task = GetPriceRona(item);
                            task.Wait();
                            if (task.Result < price)
                            {
                                price = task.Result;
                                Cheapest_Store = entry.Key;
                            }
                        }
                        Console.WriteLine("\nCheapest store is: " + Cheapest_Store);
                    }
                    else
                    {
                        task = GetPriceRona(item);
                        task.Wait();
                        price = task.Result;
                    }

                    break;


                case "homedepot":
                    task = GetPriceHD(item);
                    task.Wait();
                    price = task.Result;
                    break;

                default:
                    break;
            }

            Console.WriteLine();
            Console.WriteLine("Price :$" + price.ToString());
            Console.WriteLine("Press space to exit");
            Console.ReadKey();
        }

        static async Task<float> GetPriceHD(Item item)
        {
            string responseString = string.Empty;
            HttpClient myClient = new HttpClient();
            try
            {
                myClient.DefaultRequestHeaders.Accept.TryParseAdd("application/json");

                responseString = await myClient.GetStringAsync("https://www.homedepot.ca/homedepotcacommercewebservices/v2/homedepotca/products/" + item.SKU + "/fbt/7128?checkStockAndPrice=true&lang=en");
            }
            catch (HttpRequestException e)
            {
                Console.WriteLine("Exception :{0} \n", e.Message);
            }
            responseString = responseString.Remove(0, responseString.IndexOf("formattedValue") + 20);
            responseString = responseString.Remove(responseString.IndexOf('\"'));

            return float.Parse(responseString);
        }

        static async Task<float> GetPriceRona(Item item)
        {
            var store = Rona.Rona.Stores[item.Store.Remove(0, 5).ToLower()];

            string responseString = string.Empty;
            var baseAddress = new Uri("https://www.rona.ca");
            var cookieContainer = new CookieContainer();
            using (var handler = new HttpClientHandler() { UseCookies = false })
            using (var myClient = new HttpClient(handler) { BaseAddress = baseAddress})
            {
                try
                {
                    var message = new HttpRequestMessage(HttpMethod.Get, "/webapp/wcs/stores/servlet/RonaAjaxCatalogSearchView?storeId=10151&catalogId=10051&langId=-1&searchKey=RonaEN&content=&keywords=" + item.SKU);
                    message.Headers.Add("Cookie", "__cfduid=dcae818c6188d15cadd787516924cf8f71556765319; NSC_wt_psjhjo-xxx.spob.db_iuuqt=ffffffff096c1f6c45525d5f4f58455e445a4a42378b; JSESSIONID=0002K6T8Zfg7zFyDUJFqYJfBjaM:-2A49TR; WC_PERSISTENT=YwDf4e9OovAYagvoCcvOqzsAMhk%3D%0A%3B2019-05-01+22%3A49%3A08.103_1556765319356-2351336_10151; RonaWCCookie.stores.selected=" + store.StoreID + "; RonaWCCookie.region.selected=" + store.Region + "; RonaWCCookie.province=" + store.Province + "; RonaWCCookie.storesize=" + store.StoreSize + "; autoSelectedStore=0; showModalNewsletterOnNextVisit=0; WC_SESSION_ESTABLISHED=true; WC_ACTIVEPOINTER=-1%2C10151; BVImplmain_site=16349; WC_AUTHENTICATION_124841305=124841305%2CrSre%2F593TOeSKu%2F0IGYm1SXPOMA%3D; WC_USERACTIVITY_124841305=124841305%2C10151%2Cnull%2Cnull%2C1556766269431%2Cnull%2Cnull%2Cnull%2Cnull%2Cnull%2CHsvWRagvwn9%2BViSRJGUmCdfkyT5ulzC7LOJVSgWogfNtBSnbp3MpSLPFwNFVygtEnARu%2B3eR4kFoL%2Bo%2FHv1vlOpPTUz%2FJyZI6bWfIpW3jr6IBOsq4Sq60m8HAqI0yGnulHve1Hu7p6MHIdMdJTdxktS%2BiHyt%2BUo9ktiIhDiJRCHh4JbX3zxQ61ZD7%2FiZe1cHjI6g3H%2Fta%2Bl%2FX4A%2Fxfei3%2FSOaTmZYqG%2B9qzA2n0s%2Frc%3D");
                    var result = await myClient.SendAsync(message);
                    result.EnsureSuccessStatusCode();
                    responseString = await result.Content.ReadAsStringAsync();
                }
                catch (HttpRequestException e)
                {
                    Console.WriteLine("Exception :{0} \n", e.Message);
                }
            }

            responseString = responseString.Remove(0, responseString.IndexOf("data-product-price=") + 20);
            responseString = responseString.Remove(responseString.IndexOf('\"'));

            return float.Parse(responseString);
        }
    }
}
