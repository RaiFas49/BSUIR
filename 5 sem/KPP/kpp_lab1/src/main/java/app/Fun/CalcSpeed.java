package app.Fun;

public class CalcSpeed
{
    private float mass1, mass2, speed1, speed2;
    public CalcSpeed(float mass1, float mass2, float speed1, float speed2)
    {
        this.mass1 = mass1;
        this.mass2 = mass2;
        this.speed1 = speed1;
        this.speed2 = speed2;
    }
    public float Calc()
    {
        return (mass1*speed1 + mass2*speed2)/(mass1+mass2);
    }
}
