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

    public static Dictionary<string, RonaStore> RonaStores = new Dictionary<string, RonaStore>
    {
        ["Entrepot_Laval"] = new RonaStore("Entrepot_Laval", "41010", "QUEBEC", "QC", "BIG_BOX"),
    };

}
