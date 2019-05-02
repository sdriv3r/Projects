using System;
using System.Collections.Generic;

namespace Rona
{
    public struct RonaStore
    {
        public string StoreName;
        public string StoreID;
        public string Region;
        public string Province;
        public string StoreSize;

        public RonaStore(string RonaStoreName, string RonaStoreID, string RonaRegion, string RonaProvince, string RonaStoreSize)
        {
            StoreName = RonaStoreName;
            StoreID = RonaStoreID;
            Region = RonaRegion;
            Province = RonaProvince;
            StoreSize = RonaStoreSize;
        }
    }

    public static class Rona
    {
        public static Dictionary<string, RonaStore> Stores = new Dictionary<string, RonaStore>
        {
            ["entrepot_laval"] = new RonaStore("Entrepot_Laval", "41010", "QUEBEC", "QC", "BIG_BOX"),
            ["guyracine_laval"] = new RonaStore("Guy_Racine_Laval", "04117", "QUEBEC", "QC", ""),
            ["pontviau_laval"] = new RonaStore("Pont_Viau_Laval", "44020", "QUEBEC", "QC", "PROXIMITY"),
            ["benoit_laval"] = new RonaStore("Benoit_Laval", "03425", "QUEBEC", "QC", "PROXIMITY"),
            ["vimont_laval"] = new RonaStore("Vimont_Laval", "07611", "QUEBEC", "QC", "PROXIMITY"),
            ["metro_laval"] = new RonaStore("Metro_Laval", "04921", "QUEBEC", "QC", "PROXIMITY"),

            ["nepean"] = new RonaStore("Nepean", "55550", "ONTARIO", "ON", "BIG_BOX"),
        };
    }


}
