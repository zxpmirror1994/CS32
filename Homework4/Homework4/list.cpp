void listAllAuxiliary(string path, const File* f)
{
    path += "/" + f->name();
    cout << path << endl;
    if (f == NULL)
    {
        return;
    }
    if (f->files() == NULL)
    {
        return;
    }
    for (int k = 0; k < f->files()->size(); k++)
    {
        listAllAuxiliary(path, f->files()->at(k));
    }
}
