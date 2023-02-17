#ifndef RENDERINGWORKER_H
#define RENDERINGWORKER_H

class RenderingWorker
{
public:
    static RenderingWorker& Instance()
    {
        static RenderingWorker instance;
        return instance;
    }

    RenderingWorker(RenderingWorker const&) = delete;
    void operator=(RenderingWorker const&) = delete;

private:
    RenderingWorker() {};
};

#endif // RENDERINGWORKER_H
