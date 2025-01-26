#ifndef WINDOWLIB_CHECK_BOX_H_
#define WINDOWLIB_CHECK_BOX_H_

#include "Button.h"

class CheckBox : public Button
{
public:
    CheckBox(const char *text,
        const WndPairValue &pos = { 0, 0 },
        const WndPairValue &size = { 20, 20 });

    virtual void SetWndParent(WndBase *wnd) override;

    virtual bool GetState() const;
    virtual void SetState(const bool &flag);
};

#endif /* WINDOWLIB_CHECK_BOX_H_ */
