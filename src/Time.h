
namespace XRender
{
    class Time final
    {
    public:
	    static Time& Timer();
        Time();
        const long long& GetFrameCount() const;
        void Update();
    private:
        long long framecount;
        friend class XRender;
    };
}