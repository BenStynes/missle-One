/// Name : Ben Stynes[the better ben]
/// Nickname : Styner 
#include "MyVector2.h"

/// <summary>
/// get length of vector using sqrt of the sum of the squares
/// </summary>
/// <param name="t_vector">input vector</param>
/// <returns>length</returns>
float vectorLength(sf::Vector2f t_vector)
{
	float sumOfSquares = (t_vector.x * t_vector.x ) + (t_vector.y * t_vector.y);
	const float length = sqrt(sumOfSquares);
	return length;
}
/// <summary>
///gets the  squared length of the vector by adding x squared to y squared
/// </summary>
/// <param name="t_vector"></param>
/// <returns>length squared</returns>
float vectorLengthSquared(sf::Vector2f t_vector)
{
	float lengthSquared = (t_vector.x *t_vector.x) + (t_vector.y * t_vector.y);
	return lengthSquared;
}
/// <summary>
/// multiplies ux * vy  then uy *vx ans subtracts the results giving the cross Product
/// </summary>
/// <param name="t_vectorA"></param>
/// <param name="t_VectorB"></param>
/// <returns>crossProduct</returns>
float vectorCorssProduct(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{
	float crossProduct = (t_vectorA.x * t_VectorB.y) - (t_vectorA.y * t_VectorB.x);
	return crossProduct;
}
/// <summary>
/// Gets the dot poduct by multiplying both  vectors xs together and ys together  and adding the result of each
/// giving you an anwser
/// </summary>
/// <param name="t_vectorA"></param>
/// <param name="t_VectorB"></param>
/// <returns>dotProduct</returns>
float vectorDotProduct(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{
	float dotProduct = (t_VectorB.x * t_vectorA.x) + (t_VectorB.y *t_vectorA.y);
	return dotProduct;
}
/// <summary>
/// gets the angle in between the two vectors by getting the inverse cos of the dot product divided by the magnitude of u * magnitude of x
/// to get degrees multiply by 180/Pi 
/// </summary>
/// <param name="t_vectorA"></param>
/// <param name="t_VectorB"></param>
/// <returns>angleBetween</returns>
float vectorAngleBetween(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{   
	
	float angleBetween = (acosf(vectorDotProduct(t_vectorA, t_VectorB) / (vectorLength(t_VectorB)*vectorLength(t_vectorA))))*(180 / PI);
	return angleBetween;
}
/// <summary>
/// rotates a vector by getting the cos of the radians by the x - sin of the radians by the y giving postion 1
/// for position 2 the sin of the radians by x - cos of the radians by y
/// 
/// </summary>
/// <param name="t_vector"></param>
/// <param name="t_angleRadians"></param>
/// <returns>rotatedVector</returns>
sf::Vector2f vectorRotateBy(sf::Vector2f t_vector, float t_angleRadians)
{
	sf::Vector2f rotatedVector(cos(t_angleRadians)*t_vector.x - sin(t_angleRadians)*t_vector.y,
		sin(t_angleRadians)*t_vector.x - cos(t_angleRadians) *t_vector.y);
	return  rotatedVector; 
}

/// <summary>
/// The vector projection is gotten bt getting the dot product divided by the length by the vector 
/// divided by the vector length of the vector projecting it.
/// </summary>
/// <param name="t_vector"></param>
/// <param name="t_onto"></param>
/// <returns>projectedVector</returns>
sf::Vector2f vectorProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{

	sf::Vector2f projectedVector = (vectorDotProduct(t_vector, t_onto) / vectorLength(t_onto)*(t_onto) / vectorLength(t_onto));

	return projectedVector;

}
/// <summary>
///  rejection is the vector - projected vector.
/// </summary>
/// <param name="t_vector"></param>
/// <param name="t_onto"></param>
/// <returns>rejectedVector</returns>
sf::Vector2f vectorRejection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	sf::Vector2f rejectedVector = (t_vector - vectorProjection(t_vector,t_onto));
	return rejectedVector;
}
/// <summary>
/// the scalar projection is gotten by by the magnitude of the projection
/// </summary>
/// <param name="t_vector"></param>
/// <param name="t_onto"></param>
/// <returns>scalerProj</returns>
float vectorScalarProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	float scalerProj = (vectorLength(vectorProjection(t_vector, t_onto)));
	return scalerProj;
}
/// <summary>
/// unit vector is the vector divided by the magnitude
/// </summary>
/// <param name="t_vector"></param>
/// <returns>unitVector</returns>
sf::Vector2f vectorUnitVector(sf::Vector2f t_vector)
{
	sf::Vector2f unitVector = (t_vector / vectorLength(t_vector));
	return unitVector;
}
