
vector<access> a;

while (plist[i].t0 < time) {
    vector<access> b = plist[i].get_access();
    a.insert(a.end(), b.begin(), b.end());
}


for (int t = 0; t < t_max; t++) {
    list<s> l;
    for (int i = 0; i < plist.size() && t >= plist[i].t0; i++) {
        auto lp = plist[i].get_access(t);
        l.append(lp);
    }
    laccess.append(l);

}
