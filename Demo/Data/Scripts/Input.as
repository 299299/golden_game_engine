

class GamePad
{
    float m_padMagnitude;
    float m_previousLeftStickX;
    float m_previousLeftStickY;
    float m_leftStickX;
    float m_leftStickY;
    float m_leftStickHoldTime;
    float m_rightStickX;
    float m_rightStickY;

    GamePad()
    {
        m_padMagnitude = 0;
        m_previousLeftStickX = 0;
        m_previousLeftStickY = 0;
        m_leftStickX = 0;
        m_leftStickY = 0;
        m_leftStickHoldTime = 0;
        m_rightStickX = 0;
        m_rightStickY = 0;
    }
    bool isLeftStickStationary()
    {
        return (m_leftStickHoldTime > 0.01f);
    }
    bool hasLeftStickBeenStationary(float value )
    {
        return (m_leftStickHoldTime > value);
    }
    bool isLeftStickInDeadZone()
    {
        return (m_leftStickX * m_leftStickX + m_leftStickY * m_leftStickY) < 0.1f;
    }
    bool isRightStickInDeadZone()
    {
        return (m_rightStickX * m_rightStickX + m_rightStickY * m_rightStickY) < 0.1f;
    }


    void update(float timestep)
    {
        m_previousLeftStickX = m_leftStickX;
        m_previousLeftStickY = m_leftStickY;

        Vector2 leftStick = Vector2(0,0);
        Vector2 rightStick = Vector2(0,0);

        if(xinput.IsConnected(0))
        {
            leftStick = xinput.GetLSRaw(0);
            rightStick = xinput.GetRSRaw(0);
        }
        else 
        {
            if(input.keyDown[KEY_UP])
                leftStick.y += 1;
            if(input.keyDown[KEY_DOWN])
                leftStick.y -= 1;
            if(input.keyDown[KEY_LEFT])
                leftStick.x -= 1;
            if(input.keyDown[KEY_RIGHT])
                leftStick.x += 1;
        }

        m_padMagnitude = Sqrt(leftStick.x*leftStick.x + leftStick.y*leftStick.y);
        m_leftStickX = Lerp(m_leftStickX, leftStick.x, 0.9f);
        m_leftStickY = Lerp(m_leftStickY, leftStick.y, 0.9f);
        m_rightStickX = Lerp(m_rightStickX, rightStick.x, 0.9f);
        m_rightStickY = Lerp(m_rightStickY, rightStick.y, 0.9f);
    
        float diff = (m_previousLeftStickX - m_leftStickX) * (m_previousLeftStickX - m_leftStickX) + (m_previousLeftStickY - m_leftStickY) * (m_previousLeftStickY - m_leftStickY);
        if(diff < 0.1f)      
            m_leftStickHoldTime = m_leftStickHoldTime + timestep;
        else        
            m_leftStickHoldTime = 0; 
    }
};